#include "defs.hh" 

void init(Initialisierung& data) {
    // 1. Numerische Felder mit den definierten Makros initialisieren.
    // DIES SIND DIE KRITISCHEN WERTE, DIE DAS HAUPTPROGRAMM ERWARTET!
    data.hp = HP;
    data.mana = MANA;
    data.attack = ATTACK;
    data.defense = DEFENSE;
    
    // 2. Das 'name'-Feld:
    // Im Kontext der CTF ist der Name oft optional oder muss nur nicht NULL sein.
    data.name = "Caliban";
}