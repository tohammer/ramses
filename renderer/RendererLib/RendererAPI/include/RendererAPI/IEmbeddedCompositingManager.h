//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------

#ifndef RAMSES_IEMBEDDEDCOMPOSITINGMANAGER_H
#define RAMSES_IEMBEDDEDCOMPOSITINGMANAGER_H

#include "Types.h"
#include "SceneAPI/SceneId.h"
#include "SceneAPI/WaylandIviSurfaceId.h"
#include "Collections/HashMap.h"

namespace ramses_internal
{
    using StreamTextureHandleVector = std::vector<StreamTextureHandle>;
    using SceneStreamTextures = HashMap<SceneId, StreamTextureHandleVector>;
    using UpdatedSceneIdSet = HashSet<SceneId>;

    using StreamTextureBufferUpdates = HashMap<WaylandIviSurfaceId, UInt32>;

    class IEmbeddedCompositingManager
    {
    public:
        virtual ~IEmbeddedCompositingManager(){}

        virtual void refStream(StreamTextureHandle handle, WaylandIviSurfaceId source, SceneId sceneId) = 0;
        virtual void unrefStream(StreamTextureHandle handle, WaylandIviSurfaceId source, SceneId sceneId) = 0;
        virtual void refStream(WaylandIviSurfaceId source) = 0;
        virtual void unrefStream(WaylandIviSurfaceId source) = 0;

        virtual void dispatchStateChangesOfStreamTexturesAndSources(SceneStreamTextures& streamTexturesWithStateChange, WaylandIviSurfaceIdVector& newStreams, WaylandIviSurfaceIdVector& obsoleteStreams) = 0;
        virtual void processClientRequests() = 0;
        virtual Bool hasUpdatedContentFromStreamSourcesToUpload() const = 0;
        virtual void uploadResourcesAndGetUpdates(UpdatedSceneIdSet& updatedScenes, StreamTextureBufferUpdates& bufferUpdates) = 0;
        virtual void notifyClients() = 0;
        virtual DeviceResourceHandle getCompositedTextureDeviceHandleForStreamTexture(WaylandIviSurfaceId source) const = 0;

        virtual Bool hasRealCompositor() const = 0; //TODO Mohamed: remove this as soon as EC dummy is removed
    };
}

#endif
