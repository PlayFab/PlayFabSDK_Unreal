#pragma once

#include "PFEntity.h"
#include "PFLocalUser.h"
#include <exception>
#include "Containers/StringConv.h"
#include <playfab/core/PFEntity.h>
#include <playfab/core/PFLocalUser.h>

struct PlayFabWrapperException : public std::exception
{
    PlayFabWrapperException(HRESULT hr) : errorMessage{ FString::Printf(TEXT("Unexpected error in PlayFab handle type wrapper: %llu"), hr) }
    {
    }

    const char* what() const noexcept override
    {
        auto test = StringCast<ANSICHAR>(*errorMessage);
        return test.Get();
    }

    FString const errorMessage;
};

#define THROW_IF_FAILED(hr) do { HRESULT __hrRet = hr; if (FAILED(__hrRet)) { throw PlayFabWrapperException{ __hrRet }; }} while (0, 0)

class Entity
{
public:
    // Creates a Entity by wrapping a PFEntityHandle (transfers ownership of the handle)
    static Entity Wrap(FPFEntityHandle handle)
    {
        return Entity{ handle };
    }

    static Entity Duplicate(FPFEntityHandle handle)
    {
        FPFEntityHandle duplicatedEntityHandle;
        if (!FPFEntityDuplicateHandle(handle, duplicatedEntityHandle))
        {
            throw PlayFabWrapperException(E_FAIL);
        }
        return Entity{ duplicatedEntityHandle };
    }

    Entity(Entity const& other)
    {
        if (!FPFEntityDuplicateHandle(other.m_handle, m_handle))
        {
            throw PlayFabWrapperException(E_FAIL);
        }
    }

    Entity(Entity&& other)
    {
        std::swap(m_handle, other.m_handle);
    }

    Entity& operator=(Entity other)
    {
        std::swap(m_handle, other.m_handle);
        return *this;
    }

    virtual ~Entity()
    {
        if (m_handle)
        {
            PFEntityCloseHandle(m_handle.Get());
        }
    }

    FPFEntityHandle Handle() const noexcept
    {
        return m_handle;
    }

private:
    Entity(FPFEntityHandle handle) : m_handle{ handle }
    {
    }

    FPFEntityHandle m_handle{ nullptr };
};

class LocalUser
{
public:
    static LocalUser Wrap(FPFLocalUserHandle handle)
    {
        return LocalUser{ handle };
    }

    static LocalUser Duplicate(FPFLocalUserHandle handle)
    {
        FPFLocalUserHandle duplicatedUserHandle;
        if (!FPFLocalUserDuplicateHandle(handle, duplicatedUserHandle))
        {
            throw PlayFabWrapperException(E_FAIL);
        }
        return LocalUser{ duplicatedUserHandle };
    }

    LocalUser(LocalUser const& other)
    {
        if (!FPFLocalUserDuplicateHandle(other.m_handle, m_handle))
        {
            throw PlayFabWrapperException(E_FAIL);
        }
    }

    LocalUser(LocalUser&& other)
    {
        std::swap(m_handle, other.m_handle);
    }

    LocalUser& operator=(LocalUser other)
    {
        std::swap(m_handle, other.m_handle);
        return *this;
    }

    virtual ~LocalUser()
    {
        if (m_handle)
        {
            PFLocalUserCloseHandle(m_handle.Get());
        }
    }

    FPFLocalUserHandle Handle() const noexcept
    {
        return m_handle;
    }

private:
    LocalUser(FPFLocalUserHandle handle) : m_handle{ handle }
    {
    }

    FPFLocalUserHandle m_handle{ nullptr };
};