#include "discord-ipc/base_pipe.h"

#ifdef _WIN32
#include <windows.h>
#include <assert.h>

struct windows_pipe_data {
    HANDLE pipe{ INVALID_HANDLE_VALUE };
};

base_pipe::base_pipe() {
    windows_pipe_data windows_data;
    this->data = &windows_data;
}
base_pipe::~base_pipe() {
    this->close();
}

bool base_pipe::open() {
    wchar_t pipe_name[]{ L"\\\\?\\pipe\\discord-ipc-0" };
    const size_t pipe_digit = sizeof(pipe_name) / sizeof(wchar_t) - 2;
    pipe_name[pipe_digit] = L'0';

    auto windows_data = (windows_pipe_data*)this->data;

    for (;;) {
        windows_data->pipe = ::CreateFileW(
            pipe_name, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
        if (windows_data->pipe != INVALID_HANDLE_VALUE) {
            this->is_open = true;
            return true;
        }
        auto last_error = GetLastError();
        if (last_error == ERROR_FILE_NOT_FOUND) {
            if (pipe_name[pipe_digit] < L'9') {
                pipe_name[pipe_digit]++;
                continue;
            }
        }
        else if (last_error == ERROR_PIPE_BUSY) {
            if (!WaitNamedPipeW(pipe_name, 1000)) {
                return false;
            }
            continue;
        }
        return false;
    }
}

bool base_pipe::close() {
    auto windows_data = (windows_pipe_data*)this->data;
    ::CloseHandle(windows_data->pipe);
    windows_data->pipe = INVALID_HANDLE_VALUE;
    this->is_open = false;
    return true;
}

bool base_pipe::write(const void* data, size_t length) {
    if (length == 0) {
        return true;
    }
    auto windows_data = (windows_pipe_data*)this->data;

    assert(windows_data);
    if (!windows_data) {
        return false;
    }
    if (windows_data->pipe == INVALID_HANDLE_VALUE) {
        return false;
    }
    assert(data);
    if (!data) {
        return false;
    }
    const DWORD bytes_length = (DWORD)length;
    DWORD bytes_written = 0;
    return ::WriteFile(windows_data->pipe, data, bytes_length, &bytes_written, nullptr) == TRUE && bytes_written == bytes_length;
}
bool base_pipe::read(void* data, size_t length) {
    assert(data);
    if (!data) {
        return false;
    }
    auto windows_data = (windows_pipe_data*)this->data;
    assert(windows_data);
    if (!windows_data) {
        return false;
    }
    if (windows_data->pipe == INVALID_HANDLE_VALUE) {
        return false;
    }
    DWORD bytes_available = 0;
    if (::PeekNamedPipe(windows_data->pipe, nullptr, 0, nullptr, &bytes_available, nullptr)) {
        if (bytes_available >= length) {
            DWORD bytes_to_read = (DWORD)length;
            DWORD bytes_read = 0;
            if (::ReadFile(windows_data->pipe, data, bytes_to_read, &bytes_read, nullptr) == TRUE) {
                assert(bytes_to_read == bytes_read);
                return true;
            }
            else {
                this->close();
            }
        }
    }
    else {
        this->close();
    }
    return false;
}
#endif