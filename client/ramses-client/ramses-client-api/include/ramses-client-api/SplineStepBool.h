//  -------------------------------------------------------------------------
//  Copyright (C) 2014 BMW Car IT GmbH
//  -------------------------------------------------------------------------
//  This Source Code Form is subject to the terms of the Mozilla Public
//  License, v. 2.0. If a copy of the MPL was not distributed with this
//  file, You can obtain one at https://mozilla.org/MPL/2.0/.
//  -------------------------------------------------------------------------

#ifndef RAMSES_SPLINESTEPBOOL_H
#define RAMSES_SPLINESTEPBOOL_H

#include "ramses-client-api/Spline.h"
#include "ramses-client-api/AnimationTypes.h"

namespace ramses
{
    /**
    * @brief The SplineStepBool stores spline keys of type bool that can be used for animation with step interpolation.
    */
    class RAMSES_API SplineStepBool : public Spline
    {
    public:
        /**
        * @brief Sets a spline key at given time with given value.
        *
        * @param[in] timeStamp The time stamp for the key to be set
        * @param[in] value The value for the key data.
        * @return StatusOK for success, otherwise the returned status can be used
        *         to resolve error message using getStatusMessage().
        */
        status_t setKey(splineTimeStamp_t timeStamp, bool value);

        /**
        * @brief Gets key value and time stamp for a given key index.
        *
        * @param[in] keyIndex Index of a key to get values from.
        * @param[out] timeStamp The time stamp of the key.
        * @param[out] value The value of the key data.
        * @return StatusOK for success, otherwise the returned status can be used
        *         to resolve error message using getStatusMessage().
        */
        status_t getKeyValues(splineKeyIndex_t keyIndex, splineTimeStamp_t& timeStamp, bool& value) const;

    protected:
        /**
        * @brief AnimationSystemData is the factory for creating SplineStepBool instances.
        */
        friend class AnimationSystemData;

        /**
        * @brief Constructor of SplineStepBool
        *
        * @param[in] pimpl Internal data for implementation specifics of Spline (sink - instance becomes owner)
        */
        explicit SplineStepBool(SplineImpl& pimpl);

        /**
        * @brief Destructor of the SplineStepBool
        */
        virtual ~SplineStepBool();
    };
}

#endif
