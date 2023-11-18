#pragma once

#include "utils/glm_utils.h"

#define RATIO			(.5f)
#define LIMIT				(.8f)
#define SQUARE_SIDE			(120.f)
#define SQUARES_DISTANCE	(150.f)
#define SCALE_FACTOR_X		(2.5f)
#define SCALE_FACTOR_Y		(2.5f)


namespace transf2D
{
    inline glm::mat3 Translate(float translateX, float translateY) {
        return glm::mat3(
            1, 0, 0,
            0, 1, 0,
            translateX, translateY, 1
        );

    }

    inline glm::mat3 Scale(float scaleX, float scaleY) {
        return glm::mat3(
            scaleX, 0, 0,
            0, scaleY, 0,
            0, 0, 1
        );

    }

    inline glm::mat3 Rotate(float radians) {
        return glm::mat3(
            cos(radians), -sin(radians), 0,
            sin(radians), cos(radians), 0,
            0, 0, 1
        );

    }
}
