//  -------------------------------------------------------------------------
//  Copyright (C) 2016 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------

#ifndef RAMSES_SERVICEHANDLERMOCKS_H
#define RAMSES_SERVICEHANDLERMOCKS_H

#include <gmock/gmock.h>
#include "framework_common_gmock_header.h"
#include "TransportCommon/ServiceHandlerInterfaces.h"
#include "SceneReferencing/SceneReferenceEvent.h"
#include "TransportCommon/ServiceHandlerInterfaces.h"
#include "Components/ISceneProviderEventConsumer.h"
#include "Components/CategoryInfo.h"

namespace ramses_internal
{
    class SceneProviderServiceHandlerMock : public ISceneProviderServiceHandler
    {
    public:
        SceneProviderServiceHandlerMock();
        virtual ~SceneProviderServiceHandlerMock() override;

        MOCK_METHOD(void, handleSubscribeScene, (const SceneId& sceneId, const Guid& consumerID), (override));
        MOCK_METHOD(void, handleUnsubscribeScene, (const SceneId& sceneId, const Guid& consumerID), (override));
        MOCK_METHOD(void, handleRendererEvent, (const SceneId& sceneId, const std::vector<Byte>& data, const Guid& rendererID), (override));
    };

    class SceneRendererServiceHandlerMock : public ISceneRendererServiceHandler
    {
    public:
        SceneRendererServiceHandlerMock();
        virtual ~SceneRendererServiceHandlerMock() override;

        MOCK_METHOD(void, handleNewScenesAvailable, (const SceneInfoVector& newScenes, const Guid& providerID), (override));
        MOCK_METHOD(void, handleScenesBecameUnavailable, (const SceneInfoVector& unavailableScenes, const Guid& providerID), (override));

        MOCK_METHOD(void, handleSceneNotAvailable, (const SceneId& sceneId, const Guid& providerID), (override));

        MOCK_METHOD(void, handleInitializeScene, (const SceneId& sceneId, const Guid& providerID), (override));
        MOCK_METHOD(void, handleSceneUpdate, (const SceneId& sceneId, absl::Span<const Byte> actionData, const Guid& providerID), (override));
    };

    class DcsmProviderServiceHandlerMock : public IDcsmProviderServiceHandler
    {
    public:
        DcsmProviderServiceHandlerMock();
        virtual ~DcsmProviderServiceHandlerMock() override;

        MOCK_METHOD(void, handleCanvasSizeChange, (ContentID contentID, const CategoryInfo& categoryInfo, AnimationInformation, const Guid& consumerID), (override));
        MOCK_METHOD(void, handleContentStateChange, (ContentID contentID, EDcsmState status, const CategoryInfo& categoryInfo, AnimationInformation, const Guid& consumerID), (override));
    };

    class DcsmConsumerServiceHandlerMock : public IDcsmConsumerServiceHandler
    {
    public:
        DcsmConsumerServiceHandlerMock();
        virtual ~DcsmConsumerServiceHandlerMock() override;

        MOCK_METHOD(void, handleOfferContent, (ContentID contentID, Category, ETechnicalContentType technicalContentType, const std::string& friendlyName, const Guid& providerID), (override));
        MOCK_METHOD(void, handleContentDescription, (ContentID contentID, TechnicalContentDescriptor technicalContentDescriptor, const Guid& providerID), (override));
        MOCK_METHOD(void, handleContentReady, (ContentID contentID, const Guid& providerID), (override));
        MOCK_METHOD(void, handleContentEnableFocusRequest, (ContentID contentID, int32_t focusRequest, const Guid& providerID), (override));
        MOCK_METHOD(void, handleContentDisableFocusRequest, (ContentID contentID, int32_t focusRequest, const Guid& providerID), (override));
        MOCK_METHOD(void, handleRequestStopOfferContent, (ContentID contentID, const Guid& providerID), (override));
        MOCK_METHOD(void, handleForceStopOfferContent, (ContentID contentID, const Guid& providerID), (override));
        MOCK_METHOD(void, handleUpdateContentMetadata, (ContentID contentID, DcsmMetadata metadata, const Guid& providerID), (override));
    };
}

#endif
