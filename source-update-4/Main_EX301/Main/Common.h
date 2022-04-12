#pragma once

#define SceneFlag				*(int*)0x77EBAC
#define CameraAngle				*(float*)0x7AFE98C

void InitCommon();
void ClicMouseProc();
void CheckTickCount();