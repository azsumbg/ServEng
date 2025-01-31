#pragma once

#ifdef SERVENG_EXPORTS 
#define SERVENG_API __declspec(dllexport)
#else
#define SERVENG_API __declspec(dllimport)
#endif

#include <random>

constexpr float scr_width{ 1000.0f };
constexpr float scr_height{ 800.0f };

constexpr float sky{ 50.0f };
constexpr float ground{ 750.0f };

enum class dirs { left = 0, right = 1, up = 2, dowm = 3, stop = 4 };

struct FPOINT
{
	float x{ 0 };
	float y{ 0 };
};

// GAME ACTIVE CREATURES

uint16_t no_creature{ 0 };
uint16_t fish1{ 0b0000000000000001 };
uint16_t fish2{ 0b0000000000000010 };
uint16_t fish3{ 0b0000000000000100 };
uint16_t fish4{ 0b0000000000001000 };
uint16_t fish5{ 0b0000000000010000 };
uint16_t fish6{ 0b0000000000100000 };
uint16_t fish7{ 0b0000000001000000 };
uint16_t fish8{ 0b0000000010000000 };
uint16_t fish9{ 0b0000000100000000 };

uint16_t hero{ 0b0000001000000000 };

// BACKGROUND CREATURES

uint8_t bubbles{ 0b00000001 };
uint8_t grass{ 0b00000010 };
uint8_t jelly1{ 0b00000100 };
uint8_t jelly2{ 0b00001000 };


namespace dll
{
	class SERVENG_API RANDiT
	{
		private:
			std::random_device rd{};
			std::seed_seq* sq{ nullptr };
			std::mt19937* twister{ nullptr };

		public:

			RANDiT();
			~RANDiT();

			int operator() (int min, int max);
	};

	class SERVENG_API PROTON
	{
		protected:
			float width{ 0 };
			float height{ 0 };
			PROTON* mPtr{ nullptr };

		public:
			FPOINT start{};
			FPOINT end{};
			FPOINT center{};

			PROTON(float _init_x = 0, float _init_y = 0, float _init_width = 1.0f, float _init_height = 1.0f);
			PROTON(float _init_x, float _init_y, float _init_width, float _init_height, PROTON*& heap_pointer);

			virtual ~PROTON();

			PROTON* GetThis() const;
			float GetWidth() const;
			float GetHeight() const;

			void SetEdges();
			void SetWidth(float _new_width);
			void SetHeight(float _new_height);
			void SetNewDims(float _new_width, float _new_height);
	};



}