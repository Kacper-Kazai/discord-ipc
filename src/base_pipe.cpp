#include "discord-ipc/base_pipe.h"

#ifdef _WIN32
#include <windows.h>
#include <assert.h>

struct windows_pipe : public base_pipe {
    HANDLE pipe{ INVALID_HANDLE_VALUE };
};

static windows_pipe connection;

base_pipe* base_pipe::create(){
    return &connection;
}

void base_pipe::destroy(base_pipe*& pipe){
    auto self = reinterpret_cast<windows_pipe*>(pipe);
    self->close();
    pipe = nullptr;
}

bool base_pipe::open(){
    wchar_t pipeName[]{ L"\\\\?\\pipe\\discord-ipc-0" };
    const size_t pipeDigit = sizeof(pipeName) / sizeof(wchar_t) - 2;
    pipeName[pipeDigit] = L'0';
    auto self = reinterpret_cast<windows_pipe*>(this);
    for (;;) {
        self->pipe = ::CreateFileW(
            pipeName, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
        if (self->pipe != INVALID_HANDLE_VALUE) {
            self->is_open = true;
            return true;
        }

        auto lastError = GetLastError();
        if (lastError == ERROR_FILE_NOT_FOUND) {
            if (pipeName[pipeDigit] < L'9') {
                pipeName[pipeDigit]++;
                continue;
            }
        }
        else if (lastError == ERROR_PIPE_BUSY) {
            if (!WaitNamedPipeW(pipeName, 10000)) {
                return false;
            }
            continue;
        }
        return false;
    }
}

bool base_pipe::close(){
    auto self = reinterpret_cast<windows_pipe*>(this);
    ::CloseHandle(self->pipe);
    self->pipe = INVALID_HANDLE_VALUE;
    self->is_open = false;
    return true;
}

bool base_pipe::write(const void* data, size_t length)
{
    if (length == 0) {
        return true;
    }
    auto self = reinterpret_cast<windows_pipe*>(this);
    assert(self);
    if (!self) {
        return false;
    }
    if (self->pipe == INVALID_HANDLE_VALUE) {
        return false;
    }
    assert(data);
    if (!data) {
        return false;
    }
    const DWORD bytesLength = (DWORD)length;
    DWORD bytesWritten = 0;
    return ::WriteFile(self->pipe, data, bytesLength, &bytesWritten, nullptr) == TRUE &&
        bytesWritten == bytesLength;
}

bool base_pipe::read(void* data, size_t length)
{
    assert(data);
    if (!data) {
        return false;
    }
    auto self = reinterpret_cast<windows_pipe*>(this);
    assert(self);
    if (!self) {
        return false;
    }
    if (self->pipe == INVALID_HANDLE_VALUE) {
        return false;
    }
    DWORD bytesAvailable = 0;
    if (::PeekNamedPipe(self->pipe, nullptr, 0, nullptr, &bytesAvailable, nullptr)) {
        if (bytesAvailable >= length) {
            DWORD bytesToRead = (DWORD)length;
            DWORD bytesRead = 0;
            if (::ReadFile(self->pipe, data, bytesToRead, &bytesRead, nullptr) == TRUE) {
                assert(bytesToRead == bytesRead);
                return true;
            }
            else {
                close();
            }
        }
    }
    else {
        close();
    }
    return false;
}
#endif