/*
	TPOSLC
	A LibC implementation for TPOS (Testing and Prototyping Operating System).

	Copyright © 2024 by Osher Sinai.

	This file is part of TPOSLC (Testing and Prototyping Operating System LibC).

	TPOSLC is free software:
	you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation,
	either version 3 of the License, or (at your option) any later version.

	TPOSLC is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
	without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
	See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along with TPOSLC.
	If not, see <https://www.gnu.org/licenses/>.
*/
#pragma once
#ifndef TOS_FILO_QUEUE_H
#define TOS_FILO_QUEUE_H

#include <include\stddef.h>
#include <include\string.h>
template<typename _Type, size_t _Size = 4096>
class FiloQueue {
public:
	using Type = _Type;
	static constexpr size_t BufferSize = _Size;

private:
	size_t m_Position;
	Type m_Queue[_Size];
public:
	FiloQueue() noexcept
	{

	}
	~FiloQueue() noexcept
	{

	}
	void DelayedInitialize() noexcept
	{
		memset(this->m_Queue, 0, sizeof(_Type) * _Size);
		this->m_Position = 0;
	}

	bool Push(Type entry) noexcept
	{
		bool bRet = false;
		if (!this->IsFull())
		{
			this->m_Queue[this->m_Position++] = entry;
			bRet = true;
		}
		return bRet;
	}
	Type Pop() noexcept
	{
		Type ret;
		memset(&ret, 0, sizeof(Type));
		if (this->m_Position > 0)
			ret = this->m_Queue[--this->m_Position];
		return ret;
	}

	inline size_t CountInQueue() const noexcept
	{
		return this->m_Position;
	}
	inline bool IsFull() noexcept
	{
		return this->m_Position >= _Size;
	}
	inline void Clear() noexcept
	{ 
		this->m_Position = 0;
	}
};

#endif // !TOS_FILO_QUEUE_H
