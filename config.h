

#ifndef CONFIG_CONFIG_H_
#define CONFIG_CONFIG_H_

typedef struct entry{
	char *key;
	char *value;
}entry;

typedef struct HashMap{
	entry *map;
	int size;
}HashMap;

void obtenerConfig(HashMap *hashMap);
char* obtenerConfigConcreto(HashMap* hashMap, char *key);

#endif /* CONFIG_CONFIG_H_ */
