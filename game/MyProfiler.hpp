#ifndef MYPROFILER_HPP
#define MYPROFILER_HPP
#include "commons.hpp"

class MyProfiler final : public Profiler {
    public:
        MyProfiler();

        mutable float minPower = 0.25f;
        mutable float maxPower = 1.0f;
        mutable float gridNoiseScale = 20.0f;
        mutable float dropScale = 50.0f;
        mutable float dropChance = 0.5f;
        mutable int minGridSize = 3;
        mutable int maxGridSize = 8;
        mutable int gridSizeCutoff = 4;
        mutable int gridNoiseOctaves = 2;
    private:
        void renderCustomInterface() const;
};

#endif // MYPROFILER_HPP
