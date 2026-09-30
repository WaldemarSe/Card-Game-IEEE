#include "utils.h"

#include <time.h>
#include <raymath.h>

double lastUpdate = 0;

bool wait(double intervalo){
    double agora = GetTime();

    if(agora - lastUpdate >= intervalo){
        lastUpdate = agora;
        return true;
    }
    return false;
}

int getSign(float value){
    if(value > 0){
        return 1;
    }
    if(value == 0){
        return 0;
    }
    return -1;
}

int clamp(int value, int minBound, int maxBound){
    return (value < minBound) ? minBound : (value > maxBound) ? maxBound : value;
}

float fclamp(float value, float minBound, float maxBound){
    return (value < minBound) ? minBound : (value > maxBound) ? maxBound : value;
}

void DrawArrow(Vector2 start, Vector2 end, float headLength, float headWidth, float backOffset, Color color){
    Vector2 direction = Vector2Subtract(end, start);
    float length = Vector2Length(direction);
    if (length < 1.0f) return;

    Vector2 normalizedDirection = Vector2Scale(direction, 1.0f / length);

    Vector2 a = Vector2Subtract(end, Vector2Scale(normalizedDirection, backOffset));
    Vector2 b = Vector2Add(start, Vector2Scale(normalizedDirection, backOffset));

    DrawLineEx(b, a, 2.0f, color);

    // Perpendicular for arrowhead
    Vector2 perpendicular = {-normalizedDirection.y, normalizedDirection.x};

    Vector2 basePoint = Vector2Subtract(a, Vector2Scale(normalizedDirection, headLength));

    Vector2 pointA = Vector2Add(basePoint, Vector2Scale(perpendicular, headWidth));
    Vector2 pointB = Vector2Subtract(basePoint, Vector2Scale(perpendicular, headWidth));
    Vector2 pointC = a;

    // Determine tip, left, right
    Vector2 tip, left, right;

    // 1️⃣ Tip is lowest Y
    if (pointC.y <= pointA.y && pointC.y <= pointB.y) tip = pointC;
    else if (pointA.y <= pointC.y && pointA.y <= pointB.y) tip = pointA;
    else tip = pointB;

    // 2️⃣ Right is highest X among remaining points
    if ((tip.x != pointC.x && pointC.x > pointA.x && pointC.x > pointB.x)) right = pointC;
    else if ((tip.x != pointA.x && pointA.x > pointC.x && pointA.x > pointB.x)) right = pointA;
    else right = pointB;

    // 3️⃣ Left is the remaining point
    if ((tip.x != pointC.x && right.x != pointC.x)) left = pointC;
    else if ((tip.x != pointA.x && right.x != pointA.x)) left = pointA;
    else left = pointB;

    if (Vector2Equals(tip, right)){
        right = left;
        left = pointA;
    }

    if (Vector2Equals(tip, left)){
        left = pointA;
    }

    if(right.x < left.x){
        Vector2 temp = left;
        left = right;
        right = temp;
    }

    DrawLineEx(pointC, pointA, 2.0f, color);
    DrawLineEx(pointC, pointB, 2.0f, color);
}

Vector2 getRectCenter(Rectangle rectangle){
    Vector2 center;
    center.x = rectangle.x + rectangle.width / 2.0f;
    center.y = rectangle.y + rectangle.height / 2.0f;
    return center;
}

Rectangle reduceRecSizeEvenly(Rectangle rectangle, float factor){
    Rectangle rec = rectangle;

    rec.x = rectangle.x + (rectangle.width * factor / 2);
    rec.y = rectangle.y + (rectangle.height * factor / 2);
    rec.width *= factor;
    rec.height *= factor;
    
    return rec;
}

Rectangle increaseRecSizeEvenly(Rectangle rectangle, float factor){
    Rectangle rec = rectangle;

    rec.x = (rectangle.x + rectangle.width / 2) - (rectangle.width * factor / 2);
    rec.y = (rectangle.y + rectangle.height / 2) - (rectangle.height * factor / 2);
    rec.width *= factor;
    rec.height *= factor;
    
    return rec;
}

float getVector2Angle(Vector2 v1, Vector2 v2){
    float ydif = v2.y - v1.y;
    float xdif = v2.x - v1.x;

    float angle = atan2f(ydif, xdif);
    
    return angle;
}

float linearFunction(float t){
    return t;
}

float easeInFunction(float t){
    return powf(t, 3.0f);
}

float easeOutFunction(float t){
    return (1 - powf(1 - t, 3.0f));
}

float quadraticFunction(float t){
    return pow(t, 2.0f);
}

float rootFunction(float t){
    return pow(t, 0.5f);
}

float easeInOutFunction(float t){
    float pw = t * t;
    return (pw / (2.0f * (pw - t) + 1.0f));
}

float easeInOutCubic(float t){
    return t < 0.5 ? 4 * powf(t, 3.0f) : 1 - powf(-2 * t + 2, 3.0f) / 2;
}

float easeInOutQuint(float t){
    return t < 0.5 ? 16 * powf(t, 5.0f) : 1 - powf(-2 * t + 2, 5.0f) / 2;
}

float easeInOutCirc(float t){
    return t < 0.5 ? (1 - sqrtf(1 - powf(2 * t, 2))) / 2 : (sqrtf(1 - powf(-2 * t + 2, 2)) + 1) / 2;
}

float easeInOutBack(float t){
    const float c1 = 1.70158;
    const float c2 = c1 * 1.525;

    return t < 0.5 ? (powf(2 * t, 2) * ((c2 + 1) * 2 * t - c2)) / 2 : (powf(2 * t - 2, 2) * ((c2 + 1) * (t * 2 - 2) + c2) + 2) / 2;
}

float easeOutBounce(float t) {
    const float n1 = 7.5625f;
    const float d1 = 2.75f;

    if (t < 1 / d1) {
        return n1 * t * t;
    } else if (t < 2 / d1) {
        t -= 1.5f / d1;
        return n1 * t * t + 0.75f;
    } else if (t < 2.5f / d1) {
        t -= 2.25f / d1;
        return n1 * t * t + 0.9375f;
    } else {
        t -= 2.625f / d1;
        return n1 * t * t + 0.984375f;
    }
}

float easeOutBack(float t){
    const float c1 = 1.70158;
    const float c3 = c1 + 1;

    return 1 + c3 * powf(t - 1, 3) + c1 * powf(t - 1, 2);
}

float bellFunction(float t){
    return exp(-1 * (powf(t - 0.5f, 2) / 0.03f));
}

void createAndInsertInstance(Hash* hash, int id, Item item){
    if(*hash == NULL) *hash = criaHash(23, false, 0.75f);
    inserirHash(*hash, TextFormat("%d", id), item);
}

Item removeInstance(Hash hash, int id){
    return removeHashValue(hash, TextFormat("%d", id));
}