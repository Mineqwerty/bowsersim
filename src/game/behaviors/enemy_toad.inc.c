


void enemy_toad_init(void) {
    //o->oMoveAngleYaw = random_sign() * 0x2000;
    //o->oFaceAngleYaw = random_sign() * 0x2000;
    gCurrentObject->oOpacity = 255;
    o->oEnemyToadSpeed = 1;
    o->oEnemyToadDeath = 0;
    gMarioState->spawnedObjects += 1;

    if (o->oBehParams2ndByte == 1) {
        o->oEnemyToadSpeed = 3;
        obj_scale_xyz(o, 0.25f, 0.25f, 0.25f);
    }
    if (o->oBehParams2ndByte == 2) {
        obj_scale_xyz(o, 3.0f, 3.0f, 3.0f);
    }
}

void enemy_toad_loop(void) {
int toadDetect = 2;

if (o->oBehParams2ndByte == 1) {
    toadDetect = 1;
}

if (o->oEnemyToadDeath > 0) {
    return kill_toad();
}

if (gMarioState->spawnedObjects > 14) {
    kill_toad();
}

u16 bowserPosDiff;
    bowserPosDiff = sqrtf(
    sqr(o->oPosX - gBowserObject->oPosX ) + sqr(o->oPosZ - gBowserObject->oPosZ) + sqr(o->oPosY - gBowserObject->oPosY) + 1);

if (bowserPosDiff < 100.0f * toadDetect) {
    if (o->oBehParams2ndByte != 2) {
        
    o->oEnemyToadSpeed = 0;
    
    
    if (gMarioState->bowserAttack == 2 && gBowserObject->oVelY < 0) {
        play_sound(SOUND_OBJ_UKIKI_CHATTER_LONG, gMarioState->marioObj->header.gfx.cameraToObject);
        o->oEnemyToadDeath = 3;
    }
    else {
        cur_obj_play_sound_2(SOUND_OBJ_STOMPED);
        o->oEnemyToadDeath = 1;
    }
    }
    if (o->oBehParams2ndByte == 2) {
        if (gMarioState->bowserAttack == 2 && gBowserObject->oVelY < 0) {
        play_sound(SOUND_OBJ_UKIKI_CHATTER_LONG, gMarioState->marioObj->header.gfx.cameraToObject);
        o->oEnemyToadSpeed = 0;
    o->oEnemyToadDeath = 3;
    }
    }
}

struct Object *fire;
    f32 dist;

    fire = cur_obj_find_nearest_object_with_behavior(bhvFlameMovingForwardGrowing, &dist);
    if (fire != NULL && dist < 50.0f * toadDetect) {
        o->oEnemyToadSpeed = 0;
        o->oEnemyToadDeath = 2;
        play_sound(SOUND_OBJ_UKIKI_CHATTER_LONG, gMarioState->marioObj->header.gfx.cameraToObject);
    }

    /*s16 collisionFlags;
    obj_set_hitbox(o, &sEnemyToadHitbox);
    collisionFlags = object_step();
    */
   

    o->oPosX += 5.0f * sins(o->oFaceAngleYaw) * o->oEnemyToadSpeed;
    o->oPosZ += 5.0f * coss(o->oFaceAngleYaw - 0x50) * o->oEnemyToadSpeed;

    o->oEnemyToadFloor = find_floor_height(o->oPosX, o->oPosY, o->oPosZ);
if (o->oEnemyToadFloor < -1000.0f) {
    o->oPosX -= 5.0f * sins(o->oFaceAngleYaw) * o->oEnemyToadSpeed;
    o->oPosZ -= 5.0f * coss(o->oFaceAngleYaw - 0x50) * o->oEnemyToadSpeed;

    o->oMoveAngleYaw += random_sign() * 0x400 + 0x2000;
    o->oFaceAngleYaw += random_sign() * 0x400 + 0x2000;
}

   /* if (obj_attack_collided_from_other_object(o) == 1) {
        obj_explode_and_spawn_coins(46.0f, 1);
    }
    */
}

void kill_toad(void) {
    o->oEnemyToadTimer += 1;
    switch(o->oEnemyToadDeath) {
        case 0:
        gMarioState->spawnedObjects -= 1;
        obj_mark_for_deletion(o);
        break;
        case 1: 
         if (o->oEnemyToadTimer < 16) {
             switch (o->oBehParams2ndByte) {
                 case 0:
        obj_scale_xyz(o, 1, 1.0f / o->oEnemyToadTimer, 1); break;
        case 1:
        obj_scale_xyz(o, 0.25f, 0.25f / o->oEnemyToadTimer, 0.25f); break;
        case 2:
        obj_scale_xyz(o, 3.0f, 3.0f / o->oEnemyToadTimer, 3.0f); break;
             }
        }
        else if (o->oEnemyToadTimer > 30) {
            obj_mark_for_deletion(o);
            if (gMarioState->bowserAttack == 2) {
                gMarioState->bowserPoints += 100;
            }
                else {
            gMarioState->bowserPoints += 100;
                }
            gMarioState->spawnedObjects -= 1;
        }


                switch (o->oEnemyToadTimer) {
                    case 1:
                    spawn_orange_number(1, 0, 0, 0, 13); break;
                    case 7:
                    spawn_orange_number(0, 0, 0, 0, 7); break;
                    case 13:
                    spawn_orange_number(0, 0, 0, 0, 1); break;
                        }


        break;
        case 2:
            if (o->oEnemyToadTimer == 1) {
                spawn_object(o, MODEL_RED_FLAME, bhvFlameLargeBurningOut);
            }
        else if (o->oEnemyToadTimer > 30) {
            obj_mark_for_deletion(o);
            gMarioState->bowserPoints += 200;
            gMarioState->spawnedObjects -= 1;
        }


        switch (o->oEnemyToadTimer) {
                    case 1:
                    spawn_orange_number(2, 0, 0, 0, 13); break;
                    case 7:
                    spawn_orange_number(0, 0, 0, 0, 7); break;
                    case 13:
                    spawn_orange_number(0, 0, 0, 0, 1); break;
                        }


        break;
        case 3: if (o->oEnemyToadTimer < 16) {
        switch (o->oBehParams2ndByte) {
                 case 0:
        obj_scale_xyz(o, 1, 1.0f / o->oEnemyToadTimer, 1); break;
        case 1:
        obj_scale_xyz(o, 0.25f, 0.25f / o->oEnemyToadTimer, 0.25f); break;
        case 2:
        obj_scale_xyz(o, 3.0f, 3.0f / o->oEnemyToadTimer, 3.0f); break;
             }
        }
        else if (o->oEnemyToadTimer > 30) {
            obj_mark_for_deletion(o);
            if (gMarioState->bowserAttack == 2) {
                gMarioState->bowserPoints += 250;
            }
                else {
            gMarioState->bowserPoints += 250;
                }
            gMarioState->spawnedObjects -= 1;
        }


        switch (o->oEnemyToadTimer) {
                    case 1:
                    spawn_orange_number(2, 0, 0, 0, 13); break;
                    case 7:
                    spawn_orange_number(5, 0, 0, 0, 7); break;
                    case 13:
                    spawn_orange_number(0, 0, 0, 0, 1); break;
                        }


        break;
    }
}