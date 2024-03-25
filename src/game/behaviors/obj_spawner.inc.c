void small_spawner_loop(void) {
    u8 turn;
    turn = 0x50 + (0x10 * random_sign());
    o->oFaceAngleYaw += turn;
    o->oMoveAngleYaw += turn;

    o->oSpawnCooldown += 1;

    int initRand = random_sign();
    int midRand;
    int finalRand;
    switch (initRand) {
        case 1:
            midRand = random_sign();
            if (midRand == 1) {
                finalRand = 400;
            }
            else {
                finalRand = 200;
            }
        break;

        case -1:
            midRand = random_sign();
            if (midRand == 1) {
                finalRand = -400;
            }
            else {
                finalRand = -200;
            }
        break;
    }

    int initRand2 = random_sign();
    int midRand2;
    int finalRand2;
    switch (initRand2) {
        case 1:
            midRand2 = random_sign();
            if (midRand2 == 1) {
                finalRand2 = 400;
            }
            else {
                finalRand2 = 200;
            }
        break;

        case -1:
            midRand2 = random_sign();
            if (midRand2 == 1) {
                finalRand2 = -400;
            }
            else {
                finalRand2 = -200;
            }
        break;
    }

    if (o->oSpawnCooldown >= 120 + 10 * absf( 1 + random_sign())) {

        o->oSpawnCooldown = 0 + 20*random_sign();
        if (gMarioState->spawnedObjects <= 15) {
            gMarioState->spawnedObjectsTotal += 1;
            if (gMarioState->spawnedObjectsTotal == 8) {
                spawn_object_relative(0, finalRand, 0, finalRand2, o, MODEL_BOBOMB_BUDDY, bhvBobomb);
                gMarioState->spawnedObjectsTotal = 0;
            }
            else {
                if (gCurrLevelNum == LEVEL_BOWSER_1) {
                    spawn_object_relative(0, finalRand, 0, finalRand2, o, MODEL_TOAD, bhvEnemyToad);
                }
                if (gCurrLevelNum == LEVEL_BOWSER_2) {
                    if (gMarioState->spawnedObjectsTotal == 2 || gMarioState->spawnedObjectsTotal == 4 || gMarioState->spawnedObjectsTotal == 6 || gMarioState->spawnedObjectsTotal == 7 || gMarioState->spawnedObjectsTotal == 5) {
                        spawn_object_relative(1, finalRand, 0, finalRand2, o, MODEL_TOAD, bhvEnemyToad);
                    }
                    else {
                        spawn_object_relative(0, finalRand, 0, finalRand2, o, MODEL_TOAD, bhvEnemyToad);
                    }
                }
                if (gCurrLevelNum == LEVEL_BOWSER_3) {
                    if (gMarioState->spawnedObjectsTotal == 4 || gMarioState->spawnedObjectsTotal == 6 || gMarioState->spawnedObjectsTotal == 7 || gMarioState->spawnedObjectsTotal == 5) {
                        spawn_object_relative(2, finalRand, 0, finalRand2, o, MODEL_TOAD, bhvEnemyToad);
                    }
                    else if (gMarioState->spawnedObjectsTotal == 2 || gMarioState->spawnedObjectsTotal == 3){
                        spawn_object_relative(1, finalRand, 0, finalRand2, o, MODEL_TOAD, bhvEnemyToad);
                    }
                    else {
                    spawn_object_relative(0, finalRand, 0, finalRand2, o, MODEL_TOAD, bhvEnemyToad);
                    }
                }
            }
        }
    }


}

void big_spawner_loop(void) {
    
    o->oBigSpawnCooldown += 1;

    if (o->oBigSpawnCooldown >= 800) {
        spawn_object_relative(1, 0, 0, 0, o, MODEL_BOBOMB_BUDDY, bhvBobomb);
        o->oBigSpawnCooldown = -100;
    }

    if (o->oBigSpawnCooldown < -40) {
        print_text(60, 120, "BIG BOBOMB APPEARED");
    }

}

void endless_spawner_loop(void) {
    int randHundred = random_u16() / 2621;
    // TOAD 0
    // BOBOMB 1
    // PENGUIN 2
    int spawnPick = 0;
    int spawnPool1[24] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2};
    int spawnPool2[24] = {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 3};

switch(gMarioState->challengeRating) {
    case 1:
    spawnPick = spawnPool1[randHundred];
    break;

    case 2:
    spawnPick = spawnPool2[randHundred];
    break;

}
}