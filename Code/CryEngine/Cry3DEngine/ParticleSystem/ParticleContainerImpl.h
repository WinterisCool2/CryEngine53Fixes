// Copyright 2001-2016 Crytek GmbH / Crytek Group. All rights reserved.

// -------------------------------------------------------------------------
//  Created:     21/10/2014 by Filipe amim
//  Description:
// -------------------------------------------------------------------------
//
////////////////////////////////////////////////////////////////////////////

#ifndef PARTICLECONTAINERIMPL_H
#define PARTICLECONTAINERIMPL_H

#pragma once

namespace pfx2
{

//////////////////////////////////////////////////////////////////////////
// CParticleContainer

ILINE TParticleId CParticleContainer::GetRealId(TParticleId pId) const
{
	if (pId < m_lastId)
		return pId;
	const uint numSpawn = GetNumSpawnedParticles();
	const uint gapSize = m_firstSpawnId - m_lastId;
	const uint movingId = m_lastSpawnId - min(gapSize, numSpawn);
	const uint offset = movingId - m_lastId;
	if (pId >= movingId)
		return pId - offset;
	return pId;
}

template<typename T>
ILINE void CParticleContainer::FillData(EParticleDataType type, const T& data, SUpdateRange range)
{
	// PFX2_TODO : the way it is, this function cannot be vectorized
	CRY_PFX2_ASSERT(type.info().isType<T>());
	if (HasData(type))
	{
		uint dim = type.info().dimension;
		for (uint i = 0; i < dim; ++i)
		{
			T* pBuffer = GetData<T>(type + i);
			CRY_PFX2_FOR_RANGE_PARTICLES(range)
			{
				pBuffer[particleId] = data;
			}
			CRY_PFX2_FOR_END;
		}
	}
}

ILINE void CParticleContainer::CopyData(EParticleDataType dstType, EParticleDataType srcType, SUpdateRange range)
{
	CRY_PFX2_ASSERT(dstType.info().type == srcType.info().type);
	if (HasData(dstType) && HasData(srcType))
	{
		size_t stride = dstType.info().typeSize();
		size_t count = range.m_lastParticleId - range.m_firstParticleId;
		uint dim = dstType.info().dimension;
		for (uint i = 0; i < dim; ++i)
			memcpy(
			  (byte*)m_pData[dstType + i] + stride * range.m_firstParticleId,
			  (byte*)m_pData[srcType + i] + stride * range.m_firstParticleId,
			  stride * count);
	}
}

ILINE IFStream CParticleContainer::GetIFStream(EParticleDataType type, float defaultVal) const
{
	return IFStream(GetData<float>(type), defaultVal);
}

ILINE IOFStream CParticleContainer::GetIOFStream(EParticleDataType type)
{
	return IOFStream(GetData<float>(type));
}

ILINE IVec3Stream CParticleContainer::GetIVec3Stream(EParticleDataType type, Vec3 defaultVal) const
{
	CRY_PFX2_ASSERT(type.info().isType<float>(3));
	return IVec3Stream(
	  GetData<float>(type),
	  GetData<float>(type + 1u),
	  GetData<float>(type + 2u),
	  defaultVal);
}

ILINE IOVec3Stream CParticleContainer::GetIOVec3Stream(EParticleDataType type)
{
	CRY_PFX2_ASSERT(type.info().isType<float>(3));
	return IOVec3Stream(
	  GetData<float>(type),
	  GetData<float>(type + 1u),
	  GetData<float>(type + 2u));
}

ILINE IQuatStream CParticleContainer::GetIQuatStream(EParticleDataType type, Quat defaultVal) const
{
	CRY_PFX2_ASSERT(type.info().isType<float>(4));
	return IQuatStream(
	  GetData<float>(type),
	  GetData<float>(type + 1u),
	  GetData<float>(type + 2u),
	  GetData<float>(type + 3u),
	  defaultVal);
}
ILINE IOQuatStream CParticleContainer::GetIOQuatStream(EParticleDataType type)
{
	CRY_PFX2_ASSERT(type.info().isType<float>(4));
	return IOQuatStream(
	  GetData<float>(type),
	  GetData<float>(type + 1u),
	  GetData<float>(type + 2u),
	  GetData<float>(type + 3u));
}

ILINE IColorStream CParticleContainer::GetIColorStream(EParticleDataType type) const
{
	return IColorStream(GetData<UCol>(type));
}

ILINE IOColorStream CParticleContainer::GetIOColorStream(EParticleDataType type)
{
	return IOColorStream(GetData<UCol>(type));
}

ILINE IUintStream CParticleContainer::GetIUintStream(EParticleDataType type, uint32 defaultVal) const
{
	return IUintStream(GetData<uint>(type));
}

ILINE IOUintStream CParticleContainer::GetIOUintStream(EParticleDataType type)
{
	return IOUintStream(GetData<uint>(type));
}

ILINE IPidStream CParticleContainer::GetIPidStream(EParticleDataType type, TParticleId defaultVal) const
{
	return IPidStream(GetData<TParticleId>(type));
}

ILINE IOPidStream CParticleContainer::GetIOPidStream(EParticleDataType type)
{
	return IOPidStream(GetData<TParticleId>(type));
}

template<typename T>
ILINE TIStream<T> CParticleContainer::GetTIStream(EParticleDataType type, const T& defaultVal) const
{
	return TIStream<T>(GetData<T>(type));
}

template<typename T>
ILINE TIOStream<T> CParticleContainer::GetTIOStream(EParticleDataType type)
{
	return TIOStream<T>(GetData<T>(type));
}

ILINE SUpdateRange CParticleContainer::GetFullRange() const
{
	SUpdateRange range;
	range.m_firstParticleId = 0;
	range.m_lastParticleId = GetLastParticleId();
	return range;
}

ILINE SUpdateRange CParticleContainer::GetSpawnedRange() const
{
	SUpdateRange range;
	range.m_firstParticleId = GetFirstSpawnParticleId();
	range.m_lastParticleId = GetLastParticleId();
	return range;
}

}

#endif
