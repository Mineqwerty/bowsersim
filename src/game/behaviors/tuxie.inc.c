// tuxie.c.inc

void play_penguin_walking_sound(s32 walk) {
    s32 sound;
    if (o->oSoundStateID == 0) {
        if (walk == PENGUIN_WALK_BABY)
            sound = SOUND_OBJ_BABY_PENGUIN_WALK;
        else // PENGUIN_WALK_BIG
            sound = SOUND_OBJ_BIG_PENGUIN_WALK;
        set_obj_anim_with_accel_and_sound(1, 11, sound);
    }
}

void tuxies_mother_act_2(void) {
    f32 sp24;
    UNUSED s32 unused;
    struct Object *sp1C = cur_obj_find_nearest_object_with_behavior(bhvSmallPenguin, &sp24);

    if (cur_obj_find_nearby_held_actor(bhvUnused20E0, 1000.0f) != NULL) {
        if (o->oSubAction == 0) {
            cur_obj_init_animation_with_sound(0);
            o->oForwardVel = 10.0f;
            if (800.0f < cur_obj_lateral_dist_from_mario_to_home())
                o->oSubAction = 1;
            cur_obj_rotate_yaw_toward(o->oAngleToMario, 0x400);
        } else {
            o->oForwardVel = 0.0f;
            cur_obj_init_animation_with_sound(3);
            if (cur_obj_lateral_dist_from_mario_to_home() < 700.0f)
                o->oSubAction = 0;
        }
    } else {
        o->oForwardVel = 0.0f;
        cur_obj_init_animation_with_sound(3);
    }
    if (sp1C != NULL && sp24 < 300.0f && sp1C->oHeldState != HELD_FREE) {
        o->oAction = 1;
        sp1C->oSmallPenguinUnk88 = 1;
        o->prevObj = sp1C;
    }
}

void tuxies_mother_act_1(void) {
    s32 sp2C;
    s32 sp28;
    s32 dialogID;
    switch (o->oSubAction) {
        case 0:
            cur_obj_init_animation_with_sound(3);
            if (!cur_obj_is_mario_on_platform()) {
                sp2C = (o->oBehParams >> 0x10) & 0xFF;
                sp28 = (o->prevObj->oBehParams >> 0x10) & 0xFF;
                if (sp2C == sp28)
                    dialogID = DIALOG_058;
                else
                    dialogID = DIALOG_059;
                if (cur_obj_update_dialog_with_cutscene(MARIO_DIALOG_LOOK_UP, 
                        DIALOG_FLAG_TURN_TO_MARIO, CUTSCENE_DIALOG, dialogID)) {
                    if (dialogID == DIALOG_058)
                        o->oSubAction = 1;
                    else
                        o->oSubAction = 2;
                    o->prevObj->oInteractionSubtype |= INT_SUBTYPE_DROP_IMMEDIATELY;
                }
            } else
                cur_obj_init_animation_with_sound(0);
            break;
        case 1:
            if (o->prevObj->oHeldState == HELD_FREE) {
                //! This line is was almost certainly supposed to be something
                // like o->prevObj->oInteractionSubtype &= ~INT_SUBTYPE_DROP_IMMEDIATELY;
                // however, this code uses the value of o->oInteractionSubtype
                // rather than its offset to rawData. For this object,
                // o->oInteractionSubtype is always 0, so the result is this:
                // o->prevObj->oUnknownUnk88 &= ~INT_SUBTYPE_DROP_IMMEDIATELY
                // which has no effect as o->prevObj->oUnknownUnk88 is always 0
                // or 1, which is not affected by the bitwise AND.
                o->prevObj->OBJECT_FIELD_S32(o->oInteractionSubtype) &= ~INT_SUBTYPE_DROP_IMMEDIATELY;
                obj_set_behavior(o->prevObj, bhvUnused20E0);
#ifndef VERSION_JP
                cur_obj_spawn_star_at_y_offset(3167.0f, -4300.0f, 5108.0f, 200.0f);
#else
                spawn_default_star(3500.0f, -4300.0f, 4650.0f);
#endif
                o->oAction = 2;
            }
            break;
        case 2:
            if (o->prevObj->oHeldState == HELD_FREE) {
                //! Same bug as above
                o->prevObj->OBJECT_FIELD_S32(o->oInteractionSubtype) &= ~INT_SUBTYPE_DROP_IMMEDIATELY;
                obj_set_behavior(o->prevObj, bhvPenguinBaby);
                o->oAction = 2;
            }
            break;
    }
}

void tuxies_mother_act_0(void) {
    u16 bowserPosDiff;
    bowserPosDiff = sqrtf(
    sqr(o->oPosX - gBowserObject->oPosX ) + sqr(o->oPosZ - gBowserObject->oPosZ) + sqr(o->oPosY - gBowserObject->oPosY) + 1);
    /*
    print_text_fmt_int(200, 100, "floor %d", o->oPenguinFloor);
    o->oPenguinFloor = find_floor_height(o->oPosX + sins(o->oFaceAngleYaw) * 20, o->oPosY, o->oPosZ - coss(o->oFaceAngleYaw) * 20);
if (o->oPenguinFloor < -1000.0f) {
    //o->oPosX -= 5.0f * sins(o->oFaceAngleYaw) * o->oEnemyToadSpeed;
    //o->oPosZ -= 5.0f * coss(o->oFaceAngleYaw - 0x50) * o->oEnemyToadSpeed;
    o->oMoveAngleYaw += random_u16() * 0x400 + 0x2000;
    o->oFaceAngleYaw += random_u16() * 0x400 + 0x2000;
}
*/

if (o->oPenguinDeath > 0) {
    return kill_penguin();
}

if (bowserPosDiff < 3000.0f && o->oChasingBowser == 0) {
        //cur_obj_play_sound_2(SOUND_OBJ_BIG_PENGUIN_YELL);
        o->oChasingBowser = 1;
        cur_obj_init_animation(0);
}

if (gMarioState->bowserAttack == 2 && gBowserObject->oVelY < 0 && bowserPosDiff < 250.0f) {
    o->oTimer = 0;
    o->oPenguinDeath = 1;
    play_sound(SOUND_OBJ_BIG_PENGUIN_YELL, gMarioState->marioObj->header.gfx.cameraToObject);
    return kill_penguin();
}
else if (bowserPosDiff < 200.0f && o->oDiving == 1 && gMarioState->bowserAttack != 2) {
    gMarioState->bowserDamage = 1;
}

struct Object *fire;
    f32 dist;

    fire = cur_obj_find_nearest_object_with_behavior(bhvFlameMovingForwardGrowing, &dist);
    if (fire != NULL && dist < 150.0f) {
        o->oForwardVel = 0;
        o->oPenguinDeath = 2;
        play_sound(SOUND_OBJ_BIG_PENGUIN_YELL, gMarioState->marioObj->header.gfx.cameraToObject);
    }

obj_scale_xyz(o, 3.0f, 3.0f, 3.0f);

if (bowserPosDiff > 3200.0f && o->oChasingBowser == 1) {
    o->oChasingBowser = 0;
}

if (o->oChasingBowser == 1 && o->oDiving == 0) {

    o->oForwardVel = 10.0f;
    cur_obj_rotate_yaw_toward(obj_angle_to_object(o, gBowserObject), 0x400);

    if (bowserPosDiff < 1200.0f && o->oDiving == 0 && o->oTimer > 120) {
        o->oDiving = 1;
        o->oTimer = 0;
         cur_obj_init_animation(1);
    }
}

if (o->oDiving == 1) {
    o->oForwardVel = 25.0f;


    if (o->oTimer > 90) {
        o->oDiving = 0;
        cur_obj_init_animation(0);
        //cur_obj_rotate_yaw_toward(obj_angle_to_object(o, gBowserObject), 0x8000);
        }
}
}

void (*sTuxiesMotherActions[])(void) = { tuxies_mother_act_0, tuxies_mother_act_1,
                                         tuxies_mother_act_2 };

void bhv_tuxies_mother_loop(void) {
    o->activeFlags |= ACTIVE_FLAG_UNK10;
    cur_obj_update_floor_and_walls();
    tuxies_mother_act_0();
    cur_obj_move_standard(-78);
    play_penguin_walking_sound(PENGUIN_WALK_BIG);
    o->oInteractStatus = 0;
    
}

void small_penguin_dive_with_mario(void) {
    if (mario_is_dive_sliding()) {
        o->oSmallPenguinUnk100 = o->oAction;
        o->oAction = 3;
    }
}

void small_penguin_act_2(void) {
    s32 sp1C = 0;
    if (o->oTimer == 0)
        if (cur_obj_dist_to_nearest_object_with_behavior(bhvTuxiesMother) < 1000.0f)
            sp1C = 1;
    cur_obj_init_animation_with_sound(0);
    o->oForwardVel = o->oSmallPenguinUnk104 + 3.0f;
    cur_obj_rotate_yaw_toward(o->oAngleToMario + 0x8000, o->oSmallPenguinUnk110 + 0x600);
    if (o->oDistanceToMario > o->oSmallPenguinUnk108 + 500.0f)
        o->oAction = 0;
    small_penguin_dive_with_mario();
    if (sp1C)
        o->oAction = 5;
}

void small_penguin_act_1(void) {
    cur_obj_init_animation_with_sound(0);
    o->oForwardVel = o->oSmallPenguinUnk104 + 3.0f;
    cur_obj_rotate_yaw_toward(o->oAngleToMario, o->oSmallPenguinUnk110 + 0x600);
    if (o->oDistanceToMario < o->oSmallPenguinUnk108 + 300.0f)
        o->oAction = 0;
    if (o->oDistanceToMario > 1100.0f)
        o->oAction = 0;
    small_penguin_dive_with_mario();
}

void small_penguin_act_3(void) {
    if (o->oTimer > 5) {
        if (o->oTimer == 6)
            cur_obj_play_sound_2(SOUND_OBJ_BABY_PENGUIN_DIVE);
        cur_obj_init_animation_with_sound(1);
        if (o->oTimer > 25)
            if (!mario_is_dive_sliding())
                o->oAction = 4;
    }
}

void small_penguin_act_4(void) {
    if (o->oTimer > 20) {
        o->oForwardVel = 0.0f;
        cur_obj_init_animation_with_sound(2);
        if (o->oTimer > 40)
            o->oAction = o->oSmallPenguinUnk100;
    }
}

void small_penguin_act_0(void) {
    s32 sp1C;

    sp1C = 0;
    cur_obj_init_animation_with_sound(3);
    if (o->oTimer == 0) {
        o->oSmallPenguinUnk110 = (s32)(random_float() * 0x400);
        o->oSmallPenguinUnk108 = random_float() * 100.0f;
        o->oSmallPenguinUnk104 = random_float();
        o->oForwardVel = 0.0f;
        if (cur_obj_dist_to_nearest_object_with_behavior(bhvTuxiesMother) < 1000.0f)
            sp1C = 1;
    }
    if (o->oDistanceToMario < 1000.0f && o->oSmallPenguinUnk108 + 600.0f < o->oDistanceToMario)
        o->oAction = 1;
    else if (o->oDistanceToMario < o->oSmallPenguinUnk108 + 300.0f)
        o->oAction = 2;
    if (sp1C)
        o->oAction = 5;
    if (cur_obj_mario_far_away())
        cur_obj_set_pos_to_home();
}

void small_penguin_act_5(void) {
    f32 sp24;
    s16 sp22;
    struct Object *sp1C = cur_obj_nearest_object_with_behavior(bhvTuxiesMother);
    if (sp1C != NULL) {
        if (o->oDistanceToMario < 1000.0f)
            o->oForwardVel = 2.0f;
        else
            o->oForwardVel = 0.0f;
        sp24 = dist_between_objects(o, sp1C);
        sp22 = obj_angle_to_object(o, sp1C);
        if (sp24 > 200.0f)
            cur_obj_rotate_yaw_toward(sp22, 0x400);
        else
            cur_obj_rotate_yaw_toward(sp22 + 0x8000, 0x400);
        cur_obj_init_animation_with_sound(0);
    }
    small_penguin_dive_with_mario();
}

void (*sSmallPenguinActions[])(void) = {
    small_penguin_act_0, small_penguin_act_1, small_penguin_act_2,
    small_penguin_act_3, small_penguin_act_4, small_penguin_act_5
};

void small_penguin_free_actions(void) {
    if (o->oSmallPenguinUnk88 != 0) {
        o->oAction = 5;
        o->oSmallPenguinUnk88 = 0;
    }
    cur_obj_update_floor_and_walls();
    cur_obj_call_action_function(sSmallPenguinActions);
    cur_obj_move_standard(-78);
    play_penguin_walking_sound(PENGUIN_WALK_BABY);
}

void bhv_small_penguin_loop(void) {
    switch (o->oHeldState) {
        case HELD_FREE:
            small_penguin_free_actions();
            break;
        case HELD_HELD:
            cur_obj_unrender_set_action_and_anim(0, 0);
            if (cur_obj_has_behavior(bhvPenguinBaby))
                obj_set_behavior(o, bhvSmallPenguin);
            obj_copy_pos(o, gMarioObject);
            if (gGlobalTimer % 30 == 0)
#ifndef VERSION_JP
                play_sound(SOUND_OBJ2_BABY_PENGUIN_YELL, gMarioObject->header.gfx.cameraToObject);
#else
                play_sound(SOUND_OBJ2_BABY_PENGUIN_YELL, o->header.gfx.cameraToObject);
#endif
            break;
        case HELD_THROWN:
            cur_obj_get_thrown_or_placed(0, 0, 0);
            break;
        case HELD_DROPPED:
            cur_obj_get_dropped();
            break;
    }
}

/** Geo switch logic for Tuxie's mother's eyes. Cases 0-4. Interestingly, case
 * 4 is unused, and is the eye state seen in Shoshinkai 1995 footage.
 */
Gfx *geo_switch_tuxie_mother_eyes(s32 run, struct GraphNode *node, UNUSED Mat4 *mtx) {
    struct Object *obj;
    struct GraphNodeSwitchCase *switchCase;
    s32 timer;

    if (run == TRUE) {
        obj = (struct Object *) gCurGraphNodeObject;
        switchCase = (struct GraphNodeSwitchCase *) node;
        switchCase->selectedCase = 3;

        // timer logic for blinking. uses cases 0-2.
        timer = gGlobalTimer % 50;
        if (timer < 43)
            switchCase->selectedCase = 3;
        else if (timer < 45)
            switchCase->selectedCase = 1;
        else if (timer < 47)
            switchCase->selectedCase = 2;
        else
            switchCase->selectedCase = 1;

        /** make Tuxie's Mother have angry eyes if Mario takes the correct baby
         * after giving it back. The easiest way to check this is to see if she's
         * moving, since she only does when she's chasing Mario.
         */
        if (segmented_to_virtual(bhvTuxiesMother) == obj->behavior)
            if (obj->oForwardVel > 5.0f)
                switchCase->selectedCase = 3;
    }
    return NULL;
}

void kill_penguin() {
    o->oForwardVel = 0.0f;
    
    switch (o->oPenguinDeath) {
        case 1:
            if (o->oTimer < 16) {
                obj_scale_xyz(o, 3.0f, 3.0f / (o->oTimer + 1), 3.0f);
            }
        break;
        case 2:
            cur_obj_init_animation(2);
            if (o->oTimer == 1) {
                spawn_object(o, MODEL_RED_FLAME, bhvFlameLargeBurningOut);
            }
        break;
    }
    
    if (o->oTimer >= 30) {
        obj_mark_for_deletion(o);
        gMarioState->bowserPoints += 200;
            gMarioState->spawnedObjects -= 1;
    }

}