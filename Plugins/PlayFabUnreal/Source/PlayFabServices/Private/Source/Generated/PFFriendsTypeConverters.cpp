// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "PFFriendsTypeConverters.h"

const FPFFriendsExternalFriendSources ConvertExternalFriendSourcesToUnreal(const PFFriendsExternalFriendSources* enumVal)
{
	if (enumVal == nullptr) {
		return FPFFriendsExternalFriendSources::None;
	}

	switch(*enumVal)
	{
	case PFFriendsExternalFriendSources::None: return FPFFriendsExternalFriendSources::None;
	case PFFriendsExternalFriendSources::Steam: return FPFFriendsExternalFriendSources::Steam;
	case PFFriendsExternalFriendSources::Facebook: return FPFFriendsExternalFriendSources::Facebook;
	case PFFriendsExternalFriendSources::Xbox: return FPFFriendsExternalFriendSources::Xbox;
	case PFFriendsExternalFriendSources::Psn: return FPFFriendsExternalFriendSources::Psn;
	case PFFriendsExternalFriendSources::All: return FPFFriendsExternalFriendSources::All;
	default:
	return FPFFriendsExternalFriendSources::None;
	}
}

const PFFriendsExternalFriendSources ConvertExternalFriendSourcesToPlayfab(TSharedPtr<const FPFFriendsExternalFriendSources> enumVal)
{
	if (!enumVal.IsValid()) {
		return PFFriendsExternalFriendSources::None;
	}

	switch(*enumVal)
	{
	case FPFFriendsExternalFriendSources::None: return PFFriendsExternalFriendSources::None;
	case FPFFriendsExternalFriendSources::Steam: return PFFriendsExternalFriendSources::Steam;
	case FPFFriendsExternalFriendSources::Facebook: return PFFriendsExternalFriendSources::Facebook;
	case FPFFriendsExternalFriendSources::Xbox: return PFFriendsExternalFriendSources::Xbox;
	case FPFFriendsExternalFriendSources::Psn: return PFFriendsExternalFriendSources::Psn;
	case FPFFriendsExternalFriendSources::All: return PFFriendsExternalFriendSources::All;
	default:
	return PFFriendsExternalFriendSources::None;
	}
}

TSharedPtr<const FPFFriendsClientAddFriendRequest> ConvertClientAddFriendRequestToUnreal(const PFFriendsClientAddFriendRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFFriendsClientAddFriendRequest> ConvertedType = MakeShared<FPFFriendsClientAddFriendRequest>(FPFFriendsClientAddFriendRequest{
		.friendEmail = Datatype->friendEmail == nullptr ? FString() : FString(Datatype->friendEmail),
		.friendPlayFabId = Datatype->friendPlayFabId == nullptr ? FString() : FString(Datatype->friendPlayFabId),
		.friendTitleDisplayName = Datatype->friendTitleDisplayName == nullptr ? FString() : FString(Datatype->friendTitleDisplayName),
		.friendUsername = Datatype->friendUsername == nullptr ? FString() : FString(Datatype->friendUsername)
	});

	return ConvertedType;
}

const PFFriendsClientAddFriendRequest* ConvertClientAddFriendRequestToPlayfab(TSharedPtr<const FPFFriendsClientAddFriendRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFFriendsClientAddFriendRequest* ConvertedType = new PFFriendsClientAddFriendRequest{
		.friendEmail = ConvertFStringToCharPtr(Datatype->friendEmail),
		.friendPlayFabId = ConvertFStringToCharPtr(Datatype->friendPlayFabId),
		.friendTitleDisplayName = ConvertFStringToCharPtr(Datatype->friendTitleDisplayName),
		.friendUsername = ConvertFStringToCharPtr(Datatype->friendUsername)
	};

	return ConvertedType;
}

TSharedPtr<const FPFFriendsAddFriendResult> ConvertAddFriendResultToUnreal(const PFFriendsAddFriendResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFFriendsAddFriendResult> ConvertedType = MakeShared<FPFFriendsAddFriendResult>(FPFFriendsAddFriendResult{
		.created = Datatype->created
	});

	return ConvertedType;
}

const PFFriendsAddFriendResult* ConvertAddFriendResultToPlayfab(TSharedPtr<const FPFFriendsAddFriendResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFFriendsAddFriendResult* ConvertedType = new PFFriendsAddFriendResult{
		.created = Datatype->created
	};

	return ConvertedType;
}

TSharedPtr<const FPFFriendsClientGetFriendsListRequest> ConvertClientGetFriendsListRequestToUnreal(const PFFriendsClientGetFriendsListRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFFriendsClientGetFriendsListRequest> ConvertedType = MakeShared<FPFFriendsClientGetFriendsListRequest>(FPFFriendsClientGetFriendsListRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.externalPlatformFriends = MakeShared<FPFFriendsExternalFriendSources>(ConvertExternalFriendSourcesToUnreal(Datatype->externalPlatformFriends)),
		.profileConstraints = ConvertPlayerProfileViewConstraintsToUnreal(Datatype->profileConstraints),
#if defined(PF_GDK_AVAILABLE) && defined(PF_UE_GDK_SUPPORT)
		.user = Datatype->user == nullptr ? FGDKUserHandle() : FGDKUserHandle(Datatype->user)
#elif defined(PF_GDK_AVAILABLE)
		.user = Datatype->user == nullptr ? XUserHandle() : Datatype->user
#else
		.xboxToken = Datatype->xboxToken == nullptr ? FString() : FString(Datatype->xboxToken)
#endif
	});

	return ConvertedType;
}

const PFFriendsClientGetFriendsListRequest* ConvertClientGetFriendsListRequestToPlayfab(TSharedPtr<const FPFFriendsClientGetFriendsListRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFFriendsClientGetFriendsListRequest* ConvertedType = new PFFriendsClientGetFriendsListRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.externalPlatformFriends = new PFFriendsExternalFriendSources(ConvertExternalFriendSourcesToPlayfab(Datatype->externalPlatformFriends)),
		.profileConstraints = ConvertPlayerProfileViewConstraintsToPlayfab(Datatype->profileConstraints),
#if defined(PF_GDK_AVAILABLE)
		.user = Datatype->user
#else
		.xboxToken = ConvertFStringToCharPtr(Datatype->xboxToken)
#endif
	};

	return ConvertedType;
}

TSharedPtr<const FPFFriendsFriendInfo> ConvertFriendInfoToUnreal(const PFFriendsFriendInfo* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFFriendsFriendInfo> ConvertedType = MakeShared<FPFFriendsFriendInfo>(FPFFriendsFriendInfo{
		.facebookInfo = ConvertUserFacebookInfoToUnreal(Datatype->facebookInfo),
		.friendPlayFabId = Datatype->friendPlayFabId == nullptr ? FString() : FString(Datatype->friendPlayFabId),
		.gameCenterInfo = ConvertUserGameCenterInfoToUnreal(Datatype->gameCenterInfo),
		.profile = ConvertPlayerProfileModelToUnreal(Datatype->profile),
		.PSNInfo = ConvertUserPsnInfoToUnreal(Datatype->PSNInfo),
		.steamInfo = ConvertUserSteamInfoToUnreal(Datatype->steamInfo),
		.tags = ConvertCharArrayToUnreal(Datatype->tags, Datatype->tagsCount),
		.tagsCount = Datatype->tagsCount,
		.titleDisplayName = Datatype->titleDisplayName == nullptr ? FString() : FString(Datatype->titleDisplayName),
		.username = Datatype->username == nullptr ? FString() : FString(Datatype->username),
		.xboxInfo = ConvertUserXboxInfoToUnreal(Datatype->xboxInfo)
	});

	return ConvertedType;
}

const PFFriendsFriendInfo* ConvertFriendInfoToPlayfab(TSharedPtr<const FPFFriendsFriendInfo> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFFriendsFriendInfo* ConvertedType = new PFFriendsFriendInfo{
		.facebookInfo = ConvertUserFacebookInfoToPlayfab(Datatype->facebookInfo),
		.friendPlayFabId = ConvertFStringToCharPtr(Datatype->friendPlayFabId),
		.gameCenterInfo = ConvertUserGameCenterInfoToPlayfab(Datatype->gameCenterInfo),
		.profile = ConvertPlayerProfileModelToPlayfab(Datatype->profile),
		.PSNInfo = ConvertUserPsnInfoToPlayfab(Datatype->PSNInfo),
		.steamInfo = ConvertUserSteamInfoToPlayfab(Datatype->steamInfo),
		.tags = ConvertFStringArrayToPlayfab(Datatype->tags),
		.tagsCount = (uint32_t)Datatype->tags.Num(),
		.titleDisplayName = ConvertFStringToCharPtr(Datatype->titleDisplayName),
		.username = ConvertFStringToCharPtr(Datatype->username),
		.xboxInfo = ConvertUserXboxInfoToPlayfab(Datatype->xboxInfo)
	};

	return ConvertedType;
}

TSharedPtr<const FPFFriendsGetFriendsListResult> ConvertGetFriendsListResultToUnreal(const PFFriendsGetFriendsListResult* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFFriendsGetFriendsListResult> ConvertedType = MakeShared<FPFFriendsGetFriendsListResult>(FPFFriendsGetFriendsListResult{
		.friends = ConvertPlayfabArrayToUnreal(Datatype->friends, Datatype->friendsCount, ConvertFriendInfoToUnreal),
		.friendsCount = Datatype->friendsCount
	});

	return ConvertedType;
}

const PFFriendsGetFriendsListResult* ConvertGetFriendsListResultToPlayfab(TSharedPtr<const FPFFriendsGetFriendsListResult> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFFriendsGetFriendsListResult* ConvertedType = new PFFriendsGetFriendsListResult{
		.friends = ConvertUnrealArrayToPlayfab(Datatype->friends, ConvertFriendInfoToPlayfab),
		.friendsCount = (uint32_t)Datatype->friends.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFFriendsClientRemoveFriendRequest> ConvertClientRemoveFriendRequestToUnreal(const PFFriendsClientRemoveFriendRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFFriendsClientRemoveFriendRequest> ConvertedType = MakeShared<FPFFriendsClientRemoveFriendRequest>(FPFFriendsClientRemoveFriendRequest{
		.friendPlayFabId = Datatype->friendPlayFabId == nullptr ? FString() : FString(Datatype->friendPlayFabId)
	});

	return ConvertedType;
}

const PFFriendsClientRemoveFriendRequest* ConvertClientRemoveFriendRequestToPlayfab(TSharedPtr<const FPFFriendsClientRemoveFriendRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFFriendsClientRemoveFriendRequest* ConvertedType = new PFFriendsClientRemoveFriendRequest{
		.friendPlayFabId = ConvertFStringToCharPtr(Datatype->friendPlayFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFFriendsClientSetFriendTagsRequest> ConvertClientSetFriendTagsRequestToUnreal(const PFFriendsClientSetFriendTagsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFFriendsClientSetFriendTagsRequest> ConvertedType = MakeShared<FPFFriendsClientSetFriendTagsRequest>(FPFFriendsClientSetFriendTagsRequest{
		.friendPlayFabId = Datatype->friendPlayFabId == nullptr ? FString() : FString(Datatype->friendPlayFabId),
		.tags = ConvertCharArrayToUnreal(Datatype->tags, Datatype->tagsCount),
		.tagsCount = Datatype->tagsCount
	});

	return ConvertedType;
}

const PFFriendsClientSetFriendTagsRequest* ConvertClientSetFriendTagsRequestToPlayfab(TSharedPtr<const FPFFriendsClientSetFriendTagsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFFriendsClientSetFriendTagsRequest* ConvertedType = new PFFriendsClientSetFriendTagsRequest{
		.friendPlayFabId = ConvertFStringToCharPtr(Datatype->friendPlayFabId),
		.tags = ConvertFStringArrayToPlayfab(Datatype->tags),
		.tagsCount = (uint32_t)Datatype->tags.Num()
	};

	return ConvertedType;
}

TSharedPtr<const FPFFriendsServerAddFriendRequest> ConvertServerAddFriendRequestToUnreal(const PFFriendsServerAddFriendRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFFriendsServerAddFriendRequest> ConvertedType = MakeShared<FPFFriendsServerAddFriendRequest>(FPFFriendsServerAddFriendRequest{
		.friendEmail = Datatype->friendEmail == nullptr ? FString() : FString(Datatype->friendEmail),
		.friendPlayFabId = Datatype->friendPlayFabId == nullptr ? FString() : FString(Datatype->friendPlayFabId),
		.friendTitleDisplayName = Datatype->friendTitleDisplayName == nullptr ? FString() : FString(Datatype->friendTitleDisplayName),
		.friendUsername = Datatype->friendUsername == nullptr ? FString() : FString(Datatype->friendUsername),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFFriendsServerAddFriendRequest* ConvertServerAddFriendRequestToPlayfab(TSharedPtr<const FPFFriendsServerAddFriendRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFFriendsServerAddFriendRequest* ConvertedType = new PFFriendsServerAddFriendRequest{
		.friendEmail = ConvertFStringToCharPtr(Datatype->friendEmail),
		.friendPlayFabId = ConvertFStringToCharPtr(Datatype->friendPlayFabId),
		.friendTitleDisplayName = ConvertFStringToCharPtr(Datatype->friendTitleDisplayName),
		.friendUsername = ConvertFStringToCharPtr(Datatype->friendUsername),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFFriendsServerGetFriendsListRequest> ConvertServerGetFriendsListRequestToUnreal(const PFFriendsServerGetFriendsListRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFFriendsServerGetFriendsListRequest> ConvertedType = MakeShared<FPFFriendsServerGetFriendsListRequest>(FPFFriendsServerGetFriendsListRequest{
		.customTags = ConvertCharMapToUnreal(Datatype->customTags, Datatype->customTagsCount),
		.customTagsCount = Datatype->customTagsCount,
		.externalPlatformFriends = MakeShared<FPFFriendsExternalFriendSources>(ConvertExternalFriendSourcesToUnreal(Datatype->externalPlatformFriends)),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.profileConstraints = ConvertPlayerProfileViewConstraintsToUnreal(Datatype->profileConstraints),
		.xboxToken = Datatype->xboxToken == nullptr ? FString() : FString(Datatype->xboxToken)
	});

	return ConvertedType;
}

const PFFriendsServerGetFriendsListRequest* ConvertServerGetFriendsListRequestToPlayfab(TSharedPtr<const FPFFriendsServerGetFriendsListRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFFriendsServerGetFriendsListRequest* ConvertedType = new PFFriendsServerGetFriendsListRequest{
		.customTags = ConvertFStringMapToPlayfab(Datatype->customTags),
		.customTagsCount = (uint32_t)Datatype->customTags.Num(),
		.externalPlatformFriends = new PFFriendsExternalFriendSources(ConvertExternalFriendSourcesToPlayfab(Datatype->externalPlatformFriends)),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.profileConstraints = ConvertPlayerProfileViewConstraintsToPlayfab(Datatype->profileConstraints),
		.xboxToken = ConvertFStringToCharPtr(Datatype->xboxToken)
	};

	return ConvertedType;
}

TSharedPtr<const FPFFriendsServerRemoveFriendRequest> ConvertServerRemoveFriendRequestToUnreal(const PFFriendsServerRemoveFriendRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFFriendsServerRemoveFriendRequest> ConvertedType = MakeShared<FPFFriendsServerRemoveFriendRequest>(FPFFriendsServerRemoveFriendRequest{
		.friendPlayFabId = Datatype->friendPlayFabId == nullptr ? FString() : FString(Datatype->friendPlayFabId),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId)
	});

	return ConvertedType;
}

const PFFriendsServerRemoveFriendRequest* ConvertServerRemoveFriendRequestToPlayfab(TSharedPtr<const FPFFriendsServerRemoveFriendRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFFriendsServerRemoveFriendRequest* ConvertedType = new PFFriendsServerRemoveFriendRequest{
		.friendPlayFabId = ConvertFStringToCharPtr(Datatype->friendPlayFabId),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId)
	};

	return ConvertedType;
}

TSharedPtr<const FPFFriendsServerSetFriendTagsRequest> ConvertServerSetFriendTagsRequestToUnreal(const PFFriendsServerSetFriendTagsRequest* Datatype) {
	if (Datatype == nullptr)
	{
		return nullptr;
	}

	TSharedPtr<const FPFFriendsServerSetFriendTagsRequest> ConvertedType = MakeShared<FPFFriendsServerSetFriendTagsRequest>(FPFFriendsServerSetFriendTagsRequest{
		.friendPlayFabId = Datatype->friendPlayFabId == nullptr ? FString() : FString(Datatype->friendPlayFabId),
		.playFabId = Datatype->playFabId == nullptr ? FString() : FString(Datatype->playFabId),
		.tags = ConvertCharArrayToUnreal(Datatype->tags, Datatype->tagsCount),
		.tagsCount = Datatype->tagsCount
	});

	return ConvertedType;
}

const PFFriendsServerSetFriendTagsRequest* ConvertServerSetFriendTagsRequestToPlayfab(TSharedPtr<const FPFFriendsServerSetFriendTagsRequest> Datatype) {
	if (!Datatype.IsValid())
	{
		return nullptr;
	}

	const PFFriendsServerSetFriendTagsRequest* ConvertedType = new PFFriendsServerSetFriendTagsRequest{
		.friendPlayFabId = ConvertFStringToCharPtr(Datatype->friendPlayFabId),
		.playFabId = ConvertFStringToCharPtr(Datatype->playFabId),
		.tags = ConvertFStringArrayToPlayfab(Datatype->tags),
		.tagsCount = (uint32_t)Datatype->tags.Num()
	};

	return ConvertedType;
}
