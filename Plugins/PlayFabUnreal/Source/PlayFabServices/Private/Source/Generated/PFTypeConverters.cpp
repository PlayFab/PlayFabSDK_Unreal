// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFTypeConverters.h"

const FPFOperationTypes ConvertOperationTypesToUnreal(const PFOperationTypes* enumVal)
{
	if (enumVal == nullptr) {
		return FPFOperationTypes::Created;
	}

	switch(*enumVal)
	{
	case PFOperationTypes::Created: return FPFOperationTypes::Created;
	case PFOperationTypes::Updated: return FPFOperationTypes::Updated;
	case PFOperationTypes::Deleted: return FPFOperationTypes::Deleted;
	case PFOperationTypes::None: return FPFOperationTypes::None;
	default:
	return FPFOperationTypes::Created;
	}
}

const PFOperationTypes ConvertOperationTypesToPlayfab(TSharedPtr<const FPFOperationTypes> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFOperationTypes::Created;
	}

	switch(*enumVal)
	{
	case FPFOperationTypes::Created: return PFOperationTypes::Created;
	case FPFOperationTypes::Updated: return PFOperationTypes::Updated;
	case FPFOperationTypes::Deleted: return PFOperationTypes::Deleted;
	case FPFOperationTypes::None: return PFOperationTypes::None;
	default:
	return PFOperationTypes::Created;
	}
}

const FPFEventType ConvertEventTypeToUnreal(const PFEventType* enumVal)
{
	if (enumVal == nullptr) {
		return FPFEventType::None;
	}

	switch(*enumVal)
	{
	case PFEventType::None: return FPFEventType::None;
	case PFEventType::Telemetry: return FPFEventType::Telemetry;
	case PFEventType::PlayStream: return FPFEventType::PlayStream;
	default:
	return FPFEventType::None;
	}
}

const PFEventType ConvertEventTypeToPlayfab(TSharedPtr<const FPFEventType> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFEventType::None;
	}

	switch(*enumVal)
	{
	case FPFEventType::None: return PFEventType::None;
	case FPFEventType::Telemetry: return PFEventType::Telemetry;
	case FPFEventType::PlayStream: return PFEventType::PlayStream;
	default:
	return PFEventType::None;
	}
}

const FPFResetInterval ConvertResetIntervalToUnreal(const PFResetInterval* enumVal)
{
	if (enumVal == nullptr) {
		return FPFResetInterval::Manual;
	}

	switch(*enumVal)
	{
	case PFResetInterval::Manual: return FPFResetInterval::Manual;
	case PFResetInterval::Hour: return FPFResetInterval::Hour;
	case PFResetInterval::Day: return FPFResetInterval::Day;
	case PFResetInterval::Week: return FPFResetInterval::Week;
	case PFResetInterval::Month: return FPFResetInterval::Month;
	default:
	return FPFResetInterval::Manual;
	}
}

const PFResetInterval ConvertResetIntervalToPlayfab(TSharedPtr<const FPFResetInterval> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFResetInterval::Manual;
	}

	switch(*enumVal)
	{
	case FPFResetInterval::Manual: return PFResetInterval::Manual;
	case FPFResetInterval::Hour: return PFResetInterval::Hour;
	case FPFResetInterval::Day: return PFResetInterval::Day;
	case FPFResetInterval::Week: return PFResetInterval::Week;
	case FPFResetInterval::Month: return PFResetInterval::Month;
	default:
	return PFResetInterval::Manual;
	}
}

TSharedPtr<const FPFVersionConfiguration> ConvertVersionConfigurationToUnreal(const PFVersionConfiguration* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFVersionConfiguration> ConvertedType = MakeShared<FPFVersionConfiguration>(FPFVersionConfiguration{
		.maxQueryableVersions = Datatype->maxQueryableVersions,
		.resetInterval = ConvertResetIntervalToUnreal(&Datatype->resetInterval)
	});

	return ConvertedType;
}

const PFVersionConfiguration* ConvertVersionConfigurationToPlayfab(TSharedPtr<const FPFVersionConfiguration> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFVersionConfiguration* ConvertedType = new PFVersionConfiguration{
		.maxQueryableVersions = Datatype->maxQueryableVersions,
		.resetInterval = ConvertResetIntervalToPlayfab(MakeShared<FPFResetInterval>(Datatype->resetInterval))
	};

	return ConvertedType;
}
