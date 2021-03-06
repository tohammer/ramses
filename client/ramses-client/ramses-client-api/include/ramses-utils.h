//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------

#ifndef RAMSES_RAMSES_UTILS_H
#define RAMSES_RAMSES_UTILS_H

#include "ramses-client-api/TextureEnums.h"
#include "ramses-client-api/TextureSwizzle.h"
#include "ramses-framework-api/RamsesFrameworkTypes.h"
#include "ramses-framework-api/APIExport.h"

#include <vector>
#include <string>

namespace ramses
{
    class RamsesObject;
    class Effect;
    class Node;
    class Scene;
    class Texture2D;
    class UniformInput;
    class DataVector2f;
    class DataVector4f;
    struct MipLevelData;
    struct CubeMipLevelData;

    /**
     * @brief Temporary functions for convenience. All of these can be implemented on top
     * of the RAMSES Client API, but are offered here as convenience.
     */
    class RAMSES_API RamsesUtils
    {
    public:
        /**
        * @brief Converts object to a compatible object type.
        * Object can be converted to any of its base classes.
        * Eg. MeshNode can be converted to Node, SceneObject, ClientObject or RamsesObject.
        *
        * @param[in] obj RamsesObject to convert.
        * @return Pointer to an object of a specific type,
        *         NULL if object type is not compatible with desired object class.
        */
        template <typename T>
        static const T* TryConvert(const RamsesObject& obj);

        /**
        * @copydoc TryConvert()
        **/
        template <typename T>
        static T* TryConvert(RamsesObject& obj);

        /**
        * @brief Creates a Texture from the given png file.
        *
        * @param[in] pngFilePath Path to the png file to load
        * @param[in] scene Scene the texture object is to be created in
        * @param[in] swizzle Swizzling of texture color channels
        * @param[in] name Name for the created texture
        * @return Created texture object or nullptr on error
        */
        static Texture2D*  CreateTextureResourceFromPng(const char* pngFilePath, Scene& scene, const TextureSwizzle& swizzle = {}, const char* name = nullptr);

        /**
        * @brief Creates a Texture from the given png memory buffer.
        *
        * @param[in] pngData Buffer with PNG data to load
        * @param[in] scene Scene the texture object is to be created in
        * @param[in] swizzle Swizzling of texture color channels
        * @param[in] name Name for the created texture
        * @return Created texture object or nullptr on error
        */
        static Texture2D*  CreateTextureResourceFromPngBuffer(const std::vector<unsigned char>& pngData, Scene& scene, const TextureSwizzle& swizzle = {}, const char* name = nullptr);

        /**
        * @brief Generate mip maps from original texture 2D data. You obtain ownership of all the
        *        data returned in the mip map data object.
        * Note, that the original texture data gets copied and represents the first mip map level.
        * @see DeleteGeneratedMipMaps for deleting generated mip maps.
        * @param[in] width Width of the original texture.
        * @param[in] height Height of the original texture.
        * @param[in] bytesPerPixel Number of bytes stored per pixel in the original texture data.
        * @param[in] data Original texture data.
        * @param[out] mipMapCount Number of generated mip map levels.
        * @return generated mip map data. In case width or height are not values to the power of two,
        *         only the original mip map level is part of the result.
        *         You are responsible to destroy the generated data, e.g. by using RamsesUtils::DeleteGeneratedMipMaps
        */
        static MipLevelData* GenerateMipMapsTexture2D(uint32_t width, uint32_t height, uint8_t bytesPerPixel, uint8_t* data, uint32_t& mipMapCount);

        /**
        * @brief Creates a png from image data, e.g. data generated by RamsesClientService::readPixels.
        *        The image data is expected to be in the format rgba8. Width x Height x 4 (rgba8) have
        *        to exactly match the size of the image buffer, otherwise no png will be created.
        *        Also width * height cannot exceed the size 268435455 or png creation will fail.
        *
        * @param[in] filePath Path where the png will be saved
        * @param[in] imageData Buffer with rgba8 image data that should be saved to png
        * @param[in] width Width of the image
        * @param[in] height Height of the image
        * @return Success of png creation
        */
        static bool SaveImageBufferToPng(const std::string& filePath, const std::vector<uint8_t>& imageData, uint32_t width, uint32_t height);

        /**
        * @brief Creates a png from image data, e.g. data generated by RamsesClientService::readPixels.
        *        The image data is expected to be in the format rgba8. Width x Height x 4 (rgba8) have
        *        to exactly match the size of the image buffer, otherwise no png will be created.
        *        Also width * height cannot exceed the size 268435455 or png creation will fail.
        *        The image data can be flipped vertically, as the data coming from a function like RamsesClientService::readPixels
        *        gets the data from OpenGL which has the origin in the lower left corner, whereas png has the
        *        origin in the upper left corner. So to capture what you see on screen you have to set the flag
        *        flipImageBufferVertically to true.
        *
        * @param[in] filePath Path where the png will be saved
        * @param[in] imageData Buffer with rgba8 image data that should be saved to png
        * @param[in] width Width of the image
        * @param[in] height Height of the image
        * @param[in] flipImageBufferVertically Vertical Flipping of image data
        * @return Success of png creation
        */
        static bool SaveImageBufferToPng(const std::string& filePath, std::vector<uint8_t>& imageData, uint32_t width, uint32_t height, bool flipImageBufferVertically);

        /**
        * @brief Generate mip maps from original texture cube data. You obtain ownership of all the
        *        data returned in the mip map data object.
        * Note, that the original texture data gets copied and represents the first mip map level.
        * @see DeleteGeneratedMipMaps for deleting generated mip maps.
        * @param[in] faceWidth Width of the original texture.
        * @param[in] faceHeight Height of the original texture.
        * @param[in] bytesPerPixel Number of bytes stored per pixel in the original texture data.
        * @param[in] data Original texture data. Face data is expected in order [PX, NX, PY, NY, PZ, NZ]
        * @param[out] mipMapCount Number of generated mip map levels.
        * @return generated mip map data. In case width or height are not values to the power of two,
        *         only the original mip map level is part of the result.
        *         You are responsible to destroy the generated data, e.g. using RamsesUtils::DeleteGeneratedMipMaps
        */
        static CubeMipLevelData* GenerateMipMapsTextureCube(uint32_t faceWidth, uint32_t faceHeight, uint8_t bytesPerPixel, uint8_t* data, uint32_t& mipMapCount);

        /**
        * @brief Deletes mip map data created with RamsesUtils::GenerateMipMapsTexture2D.
        * @param[in, out] data Generated mip map data.
        * @param[in] mipMapCount Number of mip map levels in the generated data.
        */
        static void DeleteGeneratedMipMaps(MipLevelData*& data, uint32_t mipMapCount);

        /**
        * @brief Deletes mip map data created with RamsesUtils::GenerateMipMapsTextureCube.
        * @param[in, out] data Generated mip map data.
        * @param[in] mipMapCount Number of mip map levels in the generated data.
        */
        static void DeleteGeneratedMipMaps(CubeMipLevelData*& data, uint32_t mipMapCount);

        /**
        * @brief Returns the identifier of a node, which is printed in the renderer logs. The identifier is guaranteed to be
        * unique within a Scene until the Node is destroyed. If a Node is destroyed, a newly created Node can get the identifier
        * of the destroyed Node.
        * @param[in] node The node
        * @return the identifier of the given node.
        */
        static nodeId_t GetNodeId(const Node& node);

        /**
        * @brief   Convenience method to set perspective camera frustum using FOV and aspect ratio
        *          (like in #ramses::PerspectiveCamera::setFrustum) to two #ramses::DataObject instances
        *          which are or will be bound to a #ramses::PerspectiveCamera using #ramses::Camera::bindFrustumPlanes.
        * @details Use case example: just create the two data objects, bind them to one or more cameras
        *          and then simply use this method whenever projection parameters need to change.
        *          If not all parameters need to be modified, simply query the parameter you want to keep
        *          unchanged from the camera (e.g. #ramses::PerspectiveCamera::getAspectRatio) and use the same value here.
        *
        * @param[in] fov The vertical field of view to be set, must be > 0.
        *                This is the full vertical opening angle in degrees.
        * @param[in] aspectRatio Ratio between frustum width and height, must be > 0.
        *                        This value is generally independent from the viewport width and height
        *                        but typically matches the viewport aspect ratio.
        * @param[in] nearPlane Near plane of the camera frustum, must be > 0.
        * @param[in] farPlane Far plane of the camera frustum, must be > nearPlane.
        * @param[in] frustumPlanesData Data object where resulting first 4 frustum planes will be set to.
        * @param[in] nearFarPlanesData Data object where resulting near/far frustum planes will be set to.
        * @return True for success, false otherwise.
        */
        static bool SetPerspectiveCameraFrustumToDataObjects(float fov, float aspectRatio, float nearPlane, float farPlane, DataVector4f& frustumPlanesData, DataVector2f& nearFarPlanesData);
    };
}

#endif
