#pragma once

// Internal defines, don't edit and expect things to work
// -------------------------------------------------------

#define SERVO_MAX 4500.0  // This value represents 45 degrees and is just an
                        // arbitrary representation of servo max travel.

#define MIN_AIRSPEED_MIN 5 // m/s, used for arming check and speed scaling

#define TAKEOFF_RUDDER_WARNING_TIMEOUT 3000 //ms that GCS warning about not returning arming rudder to neutral repeats

#define GPS_GND_CRS_MIN_SPD 5 // m/s, used to set when intial_direction.heading is captured,deciding to heading lock in cruise mode, or steer_state.hold_course_cd

// failsafe
// ----------------------
enum failsafe_state {
    FAILSAFE_NONE=0,
    FAILSAFE_SHORT=1,
    FAILSAFE_LONG=2,
    FAILSAFE_GCS=3
};


// GCS failsafe types for FS_GCS_ENABL parameter
enum gcs_failsafe {
    GCS_FAILSAFE_OFF        = 0, // no GCS failsafe
    GCS_FAILSAFE_HEARTBEAT  = 1, // failsafe if we stop receiving heartbeat
    GCS_FAILSAFE_HB_RSSI    = 2, // failsafe if we stop receiving
                                 // heartbeat or if RADIO.remrssi
                                 // drops to 0
    GCS_FAILSAFE_HB_AUTO    = 3  // failsafe if we stop receiving heartbeat
                                 // while in AUTO mode
};

enum failsafe_action_short {
    FS_ACTION_SHORT_BESTGUESS = 0,      // CIRCLE/no change(if already in AUTO|GUIDED|LOITER)
    FS_ACTION_SHORT_CIRCLE = 1,
    FS_ACTION_SHORT_FBWA = 2,
    FS_ACTION_SHORT_DISABLED = 3,
    FS_ACTION_SHORT_FBWB = 4,
};

enum failsafe_action_long {
    FS_ACTION_LONG_CONTINUE = 0,
    FS_ACTION_LONG_RTL = 1,
    FS_ACTION_LONG_GLIDE = 2,
    FS_ACTION_LONG_PARACHUTE = 3,
    FS_ACTION_LONG_AUTO = 4,
    FS_ACTION_LONG_AUTOLAND = 5,
};

// type of stick mixing enabled
enum class StickMixing {
    NONE     = 0,
    FBW      = 1,
    DIRECT_REMOVED = 2,
    VTOL_YAW = 3,
    FBW_NO_PITCH = 4,
};

// values for RTL_AUTOLAND
enum class RtlAutoland {
    RTL_DISABLE = 0,
    RTL_THEN_DO_LAND_START = 1,
    RTL_IMMEDIATE_DO_LAND_START = 2,
    NO_RTL_GO_AROUND = 3,
    DO_RETURN_PATH_START = 4,
};

// PID broadcast bitmask
enum tuning_pid_bits {
    TUNING_BITS_ROLL  = (1 <<  0),
    TUNING_BITS_PITCH = (1 <<  1),
    TUNING_BITS_YAW   = (1 <<  2),
    TUNING_BITS_STEER = (1 <<  3),
    TUNING_BITS_LAND  = (1 <<  4),
    TUNING_BITS_ACCZ  = (1 <<  5),
    TUNING_BITS_END // dummy just used for static checking
};

static_assert(TUNING_BITS_END <= (1 << 24) + 1, "Tuning bit mask is too large to be set by MAVLink");

// Logging message types - only 32 messages are available to the vehicle here.
enum log_messages {
    LOG_CTUN_MSG,
    LOG_NTUN_MSG,
    LOG_STATUS_MSG,
    LOG_QTUN_MSG,
    LOG_PIQR_MSG,
    LOG_PIQP_MSG,
    LOG_PIQY_MSG,
    LOG_PIQA_MSG,
    LOG_PIDG_MSG,
    LOG_AETR_MSG,
    LOG_OFG_MSG,
    LOG_TSIT_MSG,
    LOG_TILT_MSG,
};

#define MASK_LOG_ATTITUDE_FAST          (1<<0)
#define MASK_LOG_ATTITUDE_MED           (1<<1)
#define MASK_LOG_GPS                    (1<<2)
#define MASK_LOG_PM                     (1<<3)
#define MASK_LOG_CTUN                   (1<<4)
#define MASK_LOG_NTUN                   (1<<5)
//#define MASK_LOG_MODE                 (1<<6) // no longer used
#define MASK_LOG_IMU                    (1<<7)
#define MASK_LOG_CMD                    (1<<8)
#define MASK_LOG_CURRENT                (1<<9)
#define MASK_LOG_COMPASS                (1<<10)
#define MASK_LOG_TECS                   (1<<11)
#define MASK_LOG_CAMERA                 (1<<12)
#define MASK_LOG_RC                     (1<<13)
#define MASK_LOG_SONAR                  (1<<14)
// #define MASK_LOG_ARM_DISARM             (1<<15)
#define MASK_LOG_IMU_RAW                (1UL<<19)
#define MASK_LOG_ATTITUDE_FULLRATE      (1U<<20)
#define MASK_LOG_VIDEO_STABILISATION    (1UL<<21)
#define MASK_LOG_NOTCH_FULLRATE         (1UL<<22)

enum {
    CRASH_DETECT_ACTION_BITMASK_DISABLED = 0,
    CRASH_DETECT_ACTION_BITMASK_DISARM = (1<<0),
    // note: next enum will be (1<<1), then (1<<2), then (1<<3)
};

enum class UseReverseThrust {
    AUTO_ALWAYS          = (1<<0),
    AUTO_LAND_APPROACH   = (1<<1),
    AUTO_LOITER_TO_ALT   = (1<<2),
    AUTO_LOITER_ALL      = (1<<3),
    AUTO_WAYPOINT        = (1<<4),
    LOITER               = (1<<5),
    RTL                  = (1<<6),
    CIRCLE               = (1<<7),
    CRUISE               = (1<<8),
    FBWB                 = (1<<9),
    GUIDED               = (1<<10),
    AUTO_LANDING_PATTERN = (1<<11),
    FBWA                 = (1<<12),
    ACRO                 = (1<<13),
    STABILIZE            = (1<<14),
    THERMAL              = (1<<15),
};

enum FlightOptions {
    DIRECT_RUDDER_ONLY   = (1 << 0),
    CRUISE_TRIM_THROTTLE = (1 << 1),
    DISABLE_TOFF_ATTITUDE_CHK = (1 << 2),
    CRUISE_TRIM_AIRSPEED = (1 << 3),
    CLIMB_BEFORE_TURN = (1 << 4),
    ACRO_YAW_DAMPER = (1 << 5),
    SURPRESS_TKOFF_SCALING = (1<<6),
    ENABLE_DEFAULT_AIRSPEED = (1<<7),
    GCS_REMOVE_TRIM_PITCH = (1 << 8),
    OSD_REMOVE_TRIM_PITCH = (1 << 9),
    CENTER_THROTTLE_TRIM = (1<<10),
    DISABLE_GROUND_PID_SUPPRESSION = (1<<11),
    ENABLE_LOITER_ALT_CONTROL = (1<<12),
    INDICATE_WAITING_FOR_RUDDER_NEUTRAL = (1<<13),
    IMMEDIATE_CLIMB_IN_AUTO = (1<<14),
    FLAP_ACTUAL_SPEED = (1<<15),
};

enum CrowFlapOptions {
    FLYINGWING       = (1 << 0),
    FULLSPAN         = (1 << 1),
    PROGRESSIVE_CROW = (1 << 2),
}; 


enum guided_heading_type_t {
    GUIDED_HEADING_NONE = 0, // no heading track
    GUIDED_HEADING_COG,      // maintain ground track
    GUIDED_HEADING_HEADING,  // maintain a heading
};


enum class AirMode {
    OFF,
    ON,
    ASSISTED_FLIGHT_ONLY,
};

enum class FenceAutoEnable : uint8_t {
    OFF=0,
    Auto=1,
    AutoDisableFloorOnly=2,
    WhenArmed=3
};

/*
  bitmask of options for RGFND_LANDING
 */
enum class RangeFinderUse : uint8_t {
    NONE    = 0U,
    ALL     = (1U<<0),
    TAKEOFF_LANDING = (1U<<1),
    ASSIST  = (1U<<2),
    CLIMB   = (1U<<3),
};

