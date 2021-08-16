

static struct ObjectHitbox sEnemyBombHitbox = {
    /* interactType:      */ INTERACT_GRABBABLE,
    /* downOffset:        */ 0,
    /* damageOrCoinValue: */ 0,
    /* health:            */ 0,
    /* numLootCoins:      */ 0,
    /* radius:            */ 65,
    /* height:            */ 113,
    /* hurtboxRadius:     */ 0,
    /* hurtboxHeight:     */ 0,
};

void enemy_bomb_init(void) {
    o->oMoveAngleYaw = random_sign() * 0x2000;
    o->oFaceAngleYaw = random_sign() * 0x2000;
    gCurrentObject->oOpacity = 255;
    o->oEnemyBombSpeed = 1;
    o->oEnemyBombDeath = 0;
}

void enemy_bomb_loop(void) {

if (o->oEnemyBombDeath > 0) {
    return kill_bomb();
}

u16 bowserPosDiff;
    bowserPosDiff = sqrtf(
    sqr(o->oPosX - gBowserObject->oPosX ) + sqr(o->oPosZ - gBowserObject->oPosZ) + sqr(o->oPosY - gBowserObject->oPosY) + 1);

if (bowserPosDiff < 200.0f) {
    print_text(100, 100, "AMONG US");
    o->oEnemyBombSpeed = 0;
    o->oEnemyBombDeath = 1;
}

struct Object *fire;
    f32 dist;

    fire = cur_obj_find_nearest_object_with_behavior(bhvFlameMovingForwardGrowing, &dist);
    if (fire != NULL && dist < 100.0f) {
        print_text(100, 100, "AUGHHH");
        o->oEnemyBombSpeed = 0;
    }

    /*s16 collisionFlags;
    obj_set_hitbox(o, &sEnemyToadHitbox);
    collisionFlags = object_step();
    */
    o->oPosX += 5.0f * sins(o->oFaceAngleYaw) * o->oEnemyBombSpeed;
    o->oPosZ += 5.0f * coss(o->oFaceAngleYaw - 0x50) * o->oEnemyBombSpeed;

   /* if (obj_attack_collided_from_other_object(o) == 1) {
        obj_explode_and_spawn_coins(46.0f, 1);
    }
    */
}

void kill_bomb(void) {
    o->oEnemyBombTimer += 1;
    switch(o->oEnemyBombDeath) {
        case 1: if (o->oEnemyBombTimer < 16) {
        obj_scale_xyz(o, 1, 1.0f / o->oEnemyBombTimer, 1);
        }
        else if (o->oEnemyBombTimer > 30) {
            obj_mark_for_deletion(o);
        }
        break;
        case 2:

        break;
    }
}