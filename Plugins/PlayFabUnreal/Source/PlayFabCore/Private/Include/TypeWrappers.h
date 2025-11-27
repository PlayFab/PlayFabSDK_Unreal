#pragma once

#include "PFEntity.h"
#include "PFLocalUser.h"
#include "Containers/StringConv.h"
#include <playfab/core/PFEntity.h>
#include <playfab/core/PFLocalUser.h>
#include "Engine/Engine.h"
#include "Logging/LogMacros.h"

DECLARE_LOG_CATEGORY_EXTERN(LogPlayFabTypeWrappers, Log, All);

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
            UE_LOG(LogPlayFabTypeWrappers, Error, TEXT("Failed to duplicate entity handle"));
            return Entity{ nullptr }; // Return invalid entity instead of throwing
        }
        return Entity{ duplicatedEntityHandle };
    }

    Entity(Entity const& other)
    {
        if (!FPFEntityDuplicateHandle(other.m_handle, m_handle))
        {
            UE_LOG(LogPlayFabTypeWrappers, Error, TEXT("Failed to copy entity handle"));
            m_handle = nullptr; // Set to null instead of throwing
        }
    }

    Entity(Entity&& other) noexcept
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

    bool IsValid() const noexcept
    {
        return m_handle != nullptr;
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
            UE_LOG(LogPlayFabTypeWrappers, Error, TEXT("Failed to duplicate local user handle"));
            return LocalUser{ nullptr }; // Return invalid local user instead of throwing
        }
        return LocalUser{ duplicatedUserHandle };
    }

    LocalUser(LocalUser const& other)
    {
        if (!FPFLocalUserDuplicateHandle(other.m_handle, m_handle))
        {
            UE_LOG(LogPlayFabTypeWrappers, Error, TEXT("Failed to copy local user handle"));
            m_handle = nullptr; // Set to null instead of throwing
        }
    }

    LocalUser(LocalUser&& other) noexcept
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

    bool IsValid() const noexcept
    {
        return m_handle != nullptr;
    }

private:
    LocalUser(FPFLocalUserHandle handle) : m_handle{ handle }
    {
    }

    FPFLocalUserHandle m_handle{ nullptr };
};