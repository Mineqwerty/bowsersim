#ifndef INTRO_HEADER_H
#define INTRO_HEADER_H

#include "types.h"

// geo
extern const GeoLayout intro_geo_0002D0[];
extern const GeoLayout intro_geo_mario_head_regular[];
extern const GeoLayout intro_geo_mario_head_dizzy[];
extern const GeoLayout intro_geo_000414[];

// leveldata
extern Lights1 titleScreen_f3d_material_002_lights;
extern Lights1 titleScreen_f3d_material_001_lights;
extern Lights1 titleScreen_f3d_material_lights;
extern Lights1 titleScreen_f3d_material_003_lights;
extern u8 titleScreen_bowow_rgba16[];
extern u8 titleScreen_bowser_i4[];
extern u8 titleScreen_bowser_shell_rgba16_ci8[];
extern u8 titleScreen_bowser_shell_rgba16_ci8_pal_rgba16[];
extern u8 titleScreen_bowber_i8[];
extern Vtx titleScreen_Cube_mesh_vtx_0[197];
extern Gfx titleScreen_Cube_mesh_tri_0[];
extern Vtx titleScreen_Cube_mesh_vtx_1[4];
extern Gfx titleScreen_Cube_mesh_tri_1[];
extern Vtx titleScreen_Cube_mesh_vtx_2[197];
extern Gfx titleScreen_Cube_mesh_tri_2[];
extern Vtx titleScreen_Cube_mesh_vtx_3[4];
extern Gfx titleScreen_Cube_mesh_tri_3[];
extern Gfx mat_titleScreen_f3d_material_002[];
extern Gfx mat_titleScreen_f3d_material_001[];
extern Gfx mat_titleScreen_f3d_material[];
extern Gfx mat_revert_titleScreen_f3d_material[];
extern Gfx mat_titleScreen_f3d_material_003[];
extern Gfx titleScreen_Cube_mesh[];

extern const Gfx intro_seg7_dl_0700C6A0[];
extern const f32 intro_seg7_table_0700C790[];
extern const f32 intro_seg7_table_0700C880[];

// script
extern const LevelScript level_intro_splash_screen[];
extern const LevelScript level_intro_mario_head_regular[];
extern const LevelScript level_intro_mario_head_dizzy[];
extern const LevelScript level_intro_entry_4[];
extern const LevelScript script_intro_L1[];
extern const LevelScript script_intro_L2[];
extern const LevelScript script_intro_L3[];
extern const LevelScript script_intro_L4[];
extern const LevelScript script_intro_L5[];

#endif
