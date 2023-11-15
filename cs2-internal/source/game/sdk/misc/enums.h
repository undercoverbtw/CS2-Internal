#pragma once

namespace sdk {
    enum Buttons : std::int32_t {
        InAttack = 1 << 0,
        InJump = 1 << 1,
        InDuck = 1 << 2,
        InForward = 1 << 3,
        InBack = 1 << 4,
        InUse = 1 << 5,
        InCancel = 1 << 6,
        InLeft = 1 << 7,
        InRight = 1 << 8,
        InMoveLeft = 1 << 9,
        InMoveRight = 1 << 10,
        InAttack2 = 1 << 11,
        InRun = 1 << 12,
        InReload = 1 << 13,
        InAlt1 = 1 << 14,
        InAlt2 = 1 << 15,
        InSore = 1 << 16,
        InSpeed = 1 << 17,
        InWalk = 1 << 18,
        InZoom = 1 << 19,
        InWeapon1 = 1 << 20,
        InWeapon2 = 1 << 21,
        InBullRush = 1 << 22,
        InGrenade1 = 1 << 23,
        InGrenade2 = 1 << 24,
        InAttack3 = 1 << 25
    };

    enum PlayerFlags : std::int32_t {
        OnGround = 1 << 0,
        Ducking = 1 << 1
    };
}