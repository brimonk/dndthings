#ifndef STRUCTS_H
#define STRUCTS_H

//
// NOTE (Brian) struct definitions for the entire program (probably)
//

typedef struct emap {
	char *etext;
	char *itext;
} emap;

enum {
	SOURCE_MONSTERMANUAL
};

// emap SOURCE_MAP[];

enum {
	ALIGNMENT_LG,
	ALIGNMENT_LN,
	ALIGNMENT_LE,
	ALIGNMENT_NG,
	ALIGNMENT_NN,
	ALIGNMENT_NE,
	ALIGNMENT_CG,
	ALIGNMENT_CN,
	ALIGNMENT_CE,
	ALIGNMENT_TOTAL
};

// emap ALIGNMENT_MAP[];

enum {
	SIZE_TINY,
	SIZE_SMALL,
	SIZE_MEDIUM,
	SIZE_LARGE,
	SIZE_HUGE,
	SIZE_GARGANTUAN
};

// emap SIZE_MAP[];

typedef struct monster {
	char *Name;

	int Size;
	int Alignment;
	int ArmorClass;

	int HitpointsDie;
	int HitpointsCnt;
	int HitpointsOffset;

	int SpeedGround;
	int SpeedFly;
	int SpeedSwim;
	int SpeedClimb;

	int StatStr;
	int StatDex;
	int StatCon;
	int StatInt;
	int StatWis;
	int StatCha;

	int HasLegendaryActions;

	int LanguageCommon;
	int LanguageGoblin;

	int ActionAsBonusSneak;
	int ActionAsBonusDisengage;
	int ActionAsBonusHide;

	int SourceBook;
	int SourcePage;
} monster;

typedef struct player {
} player;

#ifdef STRUCTS_IMPLEMENTATION

emap SOURCE_MAP[] = {
	{ "SOURCE_MONSTERMANUAL", "MONSTERMANUAL" }
};

emap SIZE_MAP[] = {
	{ "SIZE_TINY",       "TINY" },
	{ "SIZE_SMALL",      "SMALL" },
	{ "SIZE_MEDIUM",     "MEDIUM" },
	{ "SIZE_LARGE",      "LARGE" },
	{ "SIZE_HUGE",       "HUGE" },
	{ "SIZE_GARGANTUAN", "GARGANTUAN" }
};


emap ALIGNMENT_MAP[] = {
	{ "ALIGNMENT_LG", "LAWFULGOOD" },
	{ "ALIGNMENT_LN", "LAWFULNEUTRAL" },
	{ "ALIGNMENT_LE", "LAWFULEVIL" },
	{ "ALIGNMENT_NG", "NEUTRALGOOD" },
	{ "ALIGNMENT_NN", "NEUTRALNEUTRAL" },
	{ "ALIGNMENT_NE", "NEUTRALEVIL" },
	{ "ALIGNMENT_CG", "CHAOTICGOOD" },
	{ "ALIGNMENT_CN", "CHAOTICNEUTRAL" },
	{ "ALIGNMENT_CE", "CHAOTICEVIL" }
};

#endif // STRUCTS_IMPLEMENTATION

#endif // STRUCTS_H
