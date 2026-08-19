#include "mathGraph.h"

#include <lista.h>

#include <hash.h>
Hash mathAllInstances = NULL;

typedef struct MathGraphStr{
    int id;
    interpolationFunction interFunc;
    Rectangle frame;
    Vector2* points;
    int numPoints;
    float lineThickness;
} MathGraphStr;

static void calculatePoints(MathGraphStr* m){
    if(m->points != NULL) free(m->points);

    m->points = (Vector2*)malloc(sizeof(Vector2) * (m->numPoints + 2.0f));
    
    int j = 0;
    for(int i = 0; i < (m->numPoints + 2.0f); i += 1){
        float n = (1.0f/(m->numPoints + 1.0f)) * i;
        float v = m->interFunc(n);

        Vector2 p = {m->frame.x + m->frame.width * n, m->frame.y + m->frame.height - m->frame.height * v};
        m->points[j] = p;
        
        j += 1;
    }
}

MathGraph MathGraph_Init(interpolationFunction interFunc, int numPoints, Rectangle frame, float lineThickness){
    MathGraphStr* m = (MathGraphStr*)malloc(sizeof(MathGraphStr));

    static int id = 0;
    m->id = id;
    id += 1;

    m->interFunc = interFunc;
    m->frame = frame;
    m->lineThickness = lineThickness;
    m->numPoints = numPoints;
    m->points = NULL;

    calculatePoints(m);

    createAndInsertInstance(&mathAllInstances, m->id, m);

    return (MathGraph)m;
}

void MathGraph_Resize(MathGraph mathGraph, Rectangle frame){
    MathGraphStr* m = (MathGraphStr*)mathGraph;

    m->frame = frame;

    calculatePoints(m);
}

void MathGraph_Points(MathGraph mathGraph, int points){
    MathGraphStr* m = (MathGraphStr*)mathGraph;

    m->numPoints = points;

    calculatePoints(m);
}

void MathGraph_Draw(MathGraph mathGraph){
    MathGraphStr* m = (MathGraphStr*)mathGraph;

    DrawLineStrip(m->points, m->numPoints + 2, WHITE);

    DrawArrow((Vector2){m->frame.x, m->frame.y + m->frame.height}, (Vector2){m->frame.x + m->frame.width, m->frame.y + m->frame.height}, 5.0f, 5.0f, 0.0f, WHITE);
    DrawArrow((Vector2){m->frame.x, m->frame.y + m->frame.height}, (Vector2){m->frame.x, m->frame.y}, 5.0f, 5.0f, 0.0f, WHITE);
}

void MathGraph_FreeInstance(MathGraph mathGraph){
    MathGraphStr* m = (MathGraphStr*)mathGraph;
    free(m->points);
    free(m);
}

void MathGraph_Free(MathGraph mathGraph){
    MathGraphStr* m = (MathGraphStr*)mathGraph;
    removeInstance(mathAllInstances, m->id);

    MathGraph_FreeInstance(mathGraph);
}

void MathGraph_FreeAll(){
    destroiHash(mathAllInstances, freeExtra, MathGraph_FreeInstance);
    mathAllInstances = NULL;
}