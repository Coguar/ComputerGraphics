#pragma once


typedef std::vector<std::vector<int>> matrix;

const std::vector<int> BORDER = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
const std::vector<int> CENTER = { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 };

const matrix SQARE_SHAPE = {
	{0, 0, 0, 0},
	{0, 2, 2, 0},
	{0, 2, 2, 0},
	{0, 0, 0, 0}
};
const matrix LINE_SHAPE = {
	{ 0, 0, 3, 0 },
	{ 0, 0, 3, 0 },
	{ 0, 0, 3, 0 },
	{ 0, 0, 3, 0 }
};
const matrix T_SHAPE = {
	{ 0, 0, 0, 0 },
	{ 0, 0, 4, 0 },
	{ 0, 4, 4, 4 },
	{ 0, 0, 0, 0 }
};
const matrix L_SHAPE = {
	{ 0, 0, 0, 0 },
	{ 0, 5, 5, 0 },
	{ 0, 0, 5, 0 },
	{ 0, 0, 5, 0 }
};
const matrix J_SHAPE = {
	{ 0, 0, 0, 0 },
	{ 0, 0, 8, 8 },
	{ 0, 0, 8, 0 },
	{ 0, 0, 8, 0 }
};
const matrix LCHEAR_SHAPE = {
	{ 0, 0, 0, 0 },
	{ 0, 6, 6, 0 },
	{ 0, 0, 6, 6 },
	{ 0, 0, 0, 0 }
};
const matrix RCHEAR_SHAPE = {
	{ 0, 0, 0, 0 },
	{ 0, 0, 7, 7 },
	{ 0, 7, 7, 0 },
	{ 0, 0, 0, 0 }
};

const std::vector<matrix> SHAPES_LIST = {
	SQARE_SHAPE,
	LINE_SHAPE ,
	T_SHAPE ,
	L_SHAPE,
	J_SHAPE,
	LCHEAR_SHAPE,
	RCHEAR_SHAPE
};

const matrix ZERO_SHAPE = {
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 },
	{ 0, 0, 0, 0 }
};

const matrix ROTATE_MATRIX = {
	{ 0, 0, 1, 0 },
	{ 0, 1, 0, 0 },
	{ 1, 0, 0, 0 },
	{ 0, 0, 0, 1 }
};

const int START_DIFFICULTY_LEVEL = 10;
const float START_SPEED = 1.0f;
const float BOOST_FOR_LEVEL = 0.1f;
const float MAX_SPEED = 0.3f;
const int SCORE_BY_EMPTY_LINE = 10;

const int SQUARE_HEIGHT = 20;

const std::string LEVEL_STR = "LEVEL : ";
const std::string TARGET_STR = "TARGET : ";
const std::string PROGRESS_STR = "PROGRESS : ";
const std::string SCORE_STR = "SCORE : ";
const std::string START_STR = "PRESS SPACE TO START ";

const glm::vec2 START_STR_POS = { 200, 200 };
const glm::vec2 MENU_LEVEL_STR_POS = { 200, 100 };
const glm::vec2 LEVEL_STR_POS = { 300, 20 };
const glm::vec2 TARGET_STR_POS = { 300, 40 };
const glm::vec2 PROGRESS_STR_POS = { 300, 60 };
const glm::vec2 SCORE_STR_POS = { 300, 80 };

const std::string PAUSE_STR = "PAUSE ";
const glm::vec2 PAUSE_STR_POS = { 130, 15 };
const float PAUSE_FLASHING_TIME = 0.5f;

const int SCORE_FOR_1 = 10;
const int SCORE_FOR_2 = 30;
const int SCORE_FOR_3 = 70;
const int SCORE_FOR_4 = 150;

