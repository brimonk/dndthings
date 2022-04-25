#ifndef STRUCTS_H
#define STRUCTS_H

// Brian Chrzanowski
// 2022-04-25 00:44:52
//
// Clearly, just the structs for the dnd generator. Nothing much to see here.

enum {
	SOURCE_MONSTERMANUAL
};

char *SOURCE_MAP[] = {
	"MONSTERMANUAL"
};

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

char *ALIGNMENT_MAP[] = {
	"LAWFULGOOD",
	"LAWFULNEUTRAL",
	"LAWFULEVIL",
	"NEUTRALGOOD",
	"NEUTRALNEUTRAL",
	"NEUTRALEVIL",
	"CHAOTICGOOD",
	"CHAOTICNEUTRAL",
	"CHAOTICEVIL"
};

enum {
	SIZE_TINY,
	SIZE_SMALL,
	SIZE_MEDIUM,
	SIZE_LARGE,
	SIZE_HUGE,
	SIZE_GARGANTUAN
};

char *SIZE_MAP[] = { "TINY", "SMALL", "MEDIUM", "LARGE", "HUGE", "GARGANTUAN" };

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

#endif // STRUCTS_H
