#ifndef SCENE_HPP
#define SCENE_HPP
#include "commons.hpp"
#include "Noise.hpp"

class Scene final : public GameObject {
	public:
		Scene();

	private:
		void update(float deltaTime) override;
		void draw() const override;
		void genTexData();

		float minPower = 0.25f;
		float maxPower = 1.0f;
		float gridNoiseScale = 20.0f;
		float dropScale = 50.0f;
		float dropChance = 0.5f;
		int minGridSize = 3;
		int maxGridSize = 8;
		int gridSizeCutoff = 4;
		int gridNoiseOctaves = 2;
		vec2i offset = vec2i(0);

		MeshIndexed quad;
		ShaderProgram program;
		Texture2D tex;
		Noise n[4];
};

#endif // SCENE_HPP
