//  -------------------------------------------------------------------------
//  Copyright (C) 2016 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------

#include "SceneUtils/DataInstanceHelper.h"
#include "SceneAPI/IScene.h"
#include "SceneUtils/ISceneDataArrayAccessor.h"
#include "Scene/DataLayout.h"

namespace ramses_internal
{
    template <typename T>
    void getAndStoreInstanceFieldData(const IScene& scene, DataInstanceHandle dataInstance, DataFieldHandle dataField, DataInstanceValueVariant& value)
    {
        const T* data = ISceneDataArrayAccessor::GetDataArray<T>(&scene, dataInstance, dataField);
        value = data[0];
    }

    void DataInstanceHelper::GetInstanceFieldData(const IScene& scene, DataInstanceHandle dataInstance, DataFieldHandle dataField, DataInstanceValueVariant& value)
    {
        const ramses_internal::DataLayoutHandle dataLayoutHandle = scene.getLayoutOfDataInstance(dataInstance);
        const ramses_internal::DataLayout& layout = scene.getDataLayout(dataLayoutHandle);
        const ramses_internal::EDataType dataType = layout.getField(dataField).dataType;
        assert(layout.getField(dataField).elementCount == 1u);

        switch (dataType)
        {
        case ramses_internal::EDataType::Float:
            getAndStoreInstanceFieldData<Float>(scene, dataInstance, dataField, value);
            break;
        case ramses_internal::EDataType::Vector2F:
            getAndStoreInstanceFieldData<Vector2>(scene, dataInstance, dataField, value);
            break;
        case ramses_internal::EDataType::Vector3F:
            getAndStoreInstanceFieldData<Vector3>(scene, dataInstance, dataField, value);
            break;
        case ramses_internal::EDataType::Vector4F:
            getAndStoreInstanceFieldData<Vector4>(scene, dataInstance, dataField, value);
            break;
        case ramses_internal::EDataType::Int32:
            getAndStoreInstanceFieldData<Int32>(scene, dataInstance, dataField, value);
            break;
        case ramses_internal::EDataType::Vector2I:
            getAndStoreInstanceFieldData<Vector2i>(scene, dataInstance, dataField, value);
            break;
        case ramses_internal::EDataType::Vector3I:
            getAndStoreInstanceFieldData<Vector3i>(scene, dataInstance, dataField, value);
            break;
        case ramses_internal::EDataType::Vector4I:
            getAndStoreInstanceFieldData<Vector4i>(scene, dataInstance, dataField, value);
            break;
        case ramses_internal::EDataType::Matrix22F:
            getAndStoreInstanceFieldData<Matrix22f>(scene, dataInstance, dataField, value);
            break;
        case ramses_internal::EDataType::Matrix33F:
            getAndStoreInstanceFieldData<Matrix33f>(scene, dataInstance, dataField, value);
            break;
        case ramses_internal::EDataType::Matrix44F:
            getAndStoreInstanceFieldData<Matrix44f>(scene, dataInstance, dataField, value);
            break;
        default:
            assert(false);
            break;
        }
    }

    template <typename T>
    void setInstanceFieldData(IScene& scene, DataInstanceHandle dataInstance, DataFieldHandle dataField, const DataInstanceValueVariant& value)
    {
        const T typedValue = absl::get<T>(value);
        ISceneDataArrayAccessor::SetDataArray<T>(&scene, dataInstance, dataField, 1u, &typedValue);
    }

    void DataInstanceHelper::SetInstanceFieldData(IScene& scene, DataInstanceHandle dataInstance, DataFieldHandle dataField, const DataInstanceValueVariant& value)
    {
        const ramses_internal::DataLayoutHandle dataLayoutHandle = scene.getLayoutOfDataInstance(dataInstance);
        const ramses_internal::DataLayout& layout = scene.getDataLayout(dataLayoutHandle);
        const ramses_internal::EDataType dataType = layout.getField(dataField).dataType;
        assert(layout.getField(dataField).elementCount == 1u);

        switch (dataType)
        {
        case ramses_internal::EDataType::Float:
            setInstanceFieldData<Float>(scene, dataInstance, dataField, value);
            break;
        case ramses_internal::EDataType::Vector2F:
            setInstanceFieldData<Vector2>(scene, dataInstance, dataField, value);
            break;
        case ramses_internal::EDataType::Vector3F:
            setInstanceFieldData<Vector3>(scene, dataInstance, dataField, value);
            break;
        case ramses_internal::EDataType::Vector4F:
            setInstanceFieldData<Vector4>(scene, dataInstance, dataField, value);
            break;
        case ramses_internal::EDataType::Int32:
            setInstanceFieldData<Int32>(scene, dataInstance, dataField, value);
            break;
        case ramses_internal::EDataType::Vector2I:
            setInstanceFieldData<Vector2i>(scene, dataInstance, dataField, value);
            break;
        case ramses_internal::EDataType::Vector3I:
            setInstanceFieldData<Vector3i>(scene, dataInstance, dataField, value);
            break;
        case ramses_internal::EDataType::Vector4I:
            setInstanceFieldData<Vector4i>(scene, dataInstance, dataField, value);
            break;
        case ramses_internal::EDataType::Matrix22F:
            setInstanceFieldData<Matrix22f>(scene, dataInstance, dataField, value);
            break;
        case ramses_internal::EDataType::Matrix33F:
            setInstanceFieldData<Matrix33f>(scene, dataInstance, dataField, value);
            break;
        case ramses_internal::EDataType::Matrix44F:
            setInstanceFieldData<Matrix44f>(scene, dataInstance, dataField, value);
            break;
        default:
            assert(false);
            break;
        }
    }
}
