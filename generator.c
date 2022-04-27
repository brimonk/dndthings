#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>

#define COMMON_IMPLEMENTATION
#include "src/common.h"

#define STRUCTS_IMPLEMENTATION
#include "src/structs.h"

int FindEnumFromEMap(char *k, emap a[], size_t n)
{
	for (size_t i = 0; i < n; i++) {
		if (streq(k, a[i].itext))
			return i;
	}

	return -1;
}

// ParseMonster: parses the monster referenced at 'fp'
void ParseMonster(monster *mon, FILE *fp)
{
	char *s, *cmd, *arg;
	char buf[BUFLARGE];

	memset(mon, 0, sizeof(*mon));

	while (buf == fgets(buf, sizeof buf, fp)) {
		s = buf;

		if (s[strlen(s) - 1] == '\n')
			s[strlen(s) - 1] = 0;

		cmd = s;

		if (strlen(cmd) == 0 || cmd[0] == ';' || cmd[0] == '#')
			continue;

		arg = strchr(cmd, ' ');
		if (arg) {
			*arg = 0;
			arg++;
		}

		if (streq(cmd, "NAME")) {
			mon->Name = strdup(arg);

		} else if (streq(cmd, "SIZE")) {
		} else if (streq(cmd, "ALIGNMENT")) {
		} else if (streq(cmd, "ARMORCLASS")) {
			mon->ArmorClass = atoi(arg);

		} else if (streq(cmd, "HITPOINTSDIE")) {
			mon->HitpointsDie = atoi(arg);
		} else if (streq(cmd, "HITPOINTSCNT")) {
			mon->HitpointsCnt = atoi(arg);
		} else if (streq(cmd, "HITPOINTSOFFSET")) {
			mon->HitpointsOffset = atoi(arg);

		} else if (streq(cmd, "SPEEDGROUND")) {
			mon->SpeedGround = atoi(arg);
		} else if (streq(cmd, "SPEEDFLY")) {
			mon->SpeedFly = atoi(arg);
		} else if (streq(cmd, "SPEEDSWIM")) {
			mon->SpeedSwim = atoi(arg);
		} else if (streq(cmd, "SPEEDCLIMB")) {
			mon->SpeedClimb = atoi(arg);

		} else if (streq(cmd, "STATSTR")) {
			mon->StatStr = atoi(arg);
		} else if (streq(cmd, "STATDEX")) {
			mon->StatDex = atoi(arg);
		} else if (streq(cmd, "STATCON")) {
			mon->StatCon = atoi(arg);
		} else if (streq(cmd, "STATINT")) {
			mon->StatInt = atoi(arg);
		} else if (streq(cmd, "STATWIS")) {
			mon->StatWis = atoi(arg);
		} else if (streq(cmd, "STATCHA")) {
			mon->StatCha = atoi(arg);

		} else if (streq(cmd, "SKILLSTEALTH")) {

		} else if (streq(cmd, "DARKVISION")) {
		} else if (streq(cmd, "PASSIVEPERCEPTION")) {

		} else if (streq(cmd, "LANGUAGECOMMON")) {
			mon->LanguageCommon = true;
		} else if (streq(cmd, "LANGUAGEGOBLIN")) {
			mon->LanguageGoblin = true;

		} else if (streq(cmd, "ACTIONASBONUSDISENGAGE")) {
			mon->ActionAsBonusDisengage = true;
		} else if (streq(cmd, "ACTIONASBONUSHIDE")) {
			mon->ActionAsBonusHide = true;

		} else if (streq(cmd, "SOURCEBOOK")) {
			mon->SourceBook = FindEnumFromEMap(arg, SOURCE_MAP, ARRSIZE(SOURCE_MAP));
		} else if (streq(cmd, "SOURCEPAGE")) {
			mon->SourcePage = atoi(arg);

		} else if (streq(cmd, "CHALLENGERATING")) {
		} else {
			fprintf(stderr, "Command '%s' Unrecognized\n", cmd);
		}
	}
}

void PrintMonsters(monster *monsters, size_t n)
{
	printf("#ifndef GENERATOR_H\n");
	printf("#define GENERATOR_H\n");
	printf("\n");

	printf("#include \"structs.h\"\n");

	printf("monster MONSTERS[] = {\n");

	for (size_t i = 0; i < n; i++) {
		monster *curr;
		curr = monsters + i;

		printf("\t{");

		printf(" \"%s\", ", curr->Name);

		printf("%d, ", curr->Size);
		printf("%s, ", ALIGNMENT_MAP[curr->Alignment].etext);
		printf("%d, ", curr->ArmorClass);

		printf("%d, ", curr->HitpointsDie);
		printf("%d, ", curr->HitpointsCnt);
		printf("%d, ", curr->HitpointsOffset);

		printf("%d, ", curr->SpeedGround);
		printf("%d, ", curr->SpeedFly);
		printf("%d, ", curr->SpeedSwim);
		printf("%d, ", curr->SpeedClimb);

		printf("%d, ", curr->StatStr);
		printf("%d, ", curr->StatDex);
		printf("%d, ", curr->StatCon);
		printf("%d, ", curr->StatInt);
		printf("%d, ", curr->StatWis);
		printf("%d, ", curr->StatCha);

		printf("%d, ", curr->HasLegendaryActions);

		printf("%d, ", curr->LanguageCommon);
		printf("%d, ", curr->LanguageGoblin);

		printf("%d, ", curr->ActionAsBonusSneak);
		printf("%d, ", curr->ActionAsBonusDisengage);
		printf("%d, ", curr->ActionAsBonusHide);

		printf("%s, ", SOURCE_MAP[curr->SourceBook].etext);
		printf("%d ", curr->SourcePage);

		printf("}%s", i == n - 1 ? "\n" : ",\n");
	}

	printf("};\n");

	printf("\n");

	printf("#endif // GENERATOR_H\n");
}

int main(int argc, char **argv)
{
	DIR *dir;
	struct dirent *entry;
	struct monster *monsters;
	size_t monsters_len, monsters_cap;

	monsters = NULL;
	monsters_len = monsters_cap = 0;

	dir = opendir("monsters");
	if (dir == NULL) {
		return 1;
	}

	while ((entry = readdir(dir)) != NULL) {
		char *s = strstr(entry->d_name, ".txt");
		if (s == NULL) { // NOTE (Brian) this is scuffed AF
			continue;
		}

		char fullpath[BUFLARGE];
		snprintf(fullpath, sizeof fullpath, "%s/%s", "monsters", entry->d_name);

		FILE *fp = fopen(fullpath, "rb");
		if (fp == NULL) { // error?
			continue;
		}

		C_RESIZE(&monsters);
		ParseMonster(monsters + monsters_len++, fp);

		fclose(fp);
	}

	closedir(dir);

	PrintMonsters(monsters, monsters_len);

	return 0;
}
