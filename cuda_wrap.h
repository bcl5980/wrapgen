#pragma once
typedef unsigned __int32 cuuint32_t;
typedef unsigned __int64 cuuint64_t;
extern "C"
{
    typedef unsigned long long CUdeviceptr;
    typedef int CUdevice;
    typedef struct CUctx_st *CUcontext;
    typedef struct CUmod_st *CUmodule;
    typedef struct CUfunc_st *CUfunction;
    typedef struct CUarray_st *CUarray;
    typedef struct CUmipmappedArray_st *CUmipmappedArray;
    typedef struct CUtexref_st *CUtexref;
    typedef struct CUsurfref_st *CUsurfref;
    typedef struct CUevent_st *CUevent;
    typedef struct CUstream_st *CUstream;
    typedef struct CUgraphicsResource_st *CUgraphicsResource;
    typedef unsigned long long CUtexObject;
    typedef unsigned long long CUsurfObject;
    typedef struct CUextMemory_st *CUexternalMemory;
    typedef struct CUextSemaphore_st *CUexternalSemaphore;
    typedef struct CUgraph_st *CUgraph;
    typedef struct CUgraphNode_st *CUgraphNode;
    typedef struct CUgraphExec_st *CUgraphExec;
    typedef struct CUuuid_st {
        char bytes[16];
    } CUuuid;
    typedef struct CUipcEventHandle_st {
        char reserved[64];
    } CUipcEventHandle;
    typedef struct CUipcMemHandle_st {
        char reserved[64];
    } CUipcMemHandle;
    typedef enum CUipcMem_flags_enum {
        CU_IPC_MEM_LAZY_ENABLE_PEER_ACCESS = 0x1
    } CUipcMem_flags;
    typedef enum CUmemAttach_flags_enum {
        CU_MEM_ATTACH_GLOBAL = 0x1,
        CU_MEM_ATTACH_HOST = 0x2,
        CU_MEM_ATTACH_SINGLE = 0x4
    } CUmemAttach_flags;
    typedef enum CUctx_flags_enum {
        CU_CTX_SCHED_AUTO = 0x00,
        CU_CTX_SCHED_SPIN = 0x01,
        CU_CTX_SCHED_YIELD = 0x02,
        CU_CTX_SCHED_BLOCKING_SYNC = 0x04,
        CU_CTX_BLOCKING_SYNC = 0x04,
        CU_CTX_SCHED_MASK = 0x07,
        CU_CTX_MAP_HOST = 0x08,
        CU_CTX_LMEM_RESIZE_TO_MAX = 0x10,
        CU_CTX_FLAGS_MASK = 0x1f
    } CUctx_flags;
    typedef enum CUstream_flags_enum {
        CU_STREAM_DEFAULT = 0x0,
        CU_STREAM_NON_BLOCKING = 0x1
    } CUstream_flags;
    typedef enum CUevent_flags_enum {
        CU_EVENT_DEFAULT = 0x0,
        CU_EVENT_BLOCKING_SYNC = 0x1,
        CU_EVENT_DISABLE_TIMING = 0x2,
        CU_EVENT_INTERPROCESS = 0x4
    } CUevent_flags;
    typedef enum CUstreamWaitValue_flags_enum {
        CU_STREAM_WAIT_VALUE_GEQ = 0x0,
        CU_STREAM_WAIT_VALUE_EQ = 0x1,
        CU_STREAM_WAIT_VALUE_AND = 0x2,
        CU_STREAM_WAIT_VALUE_NOR = 0x3,
        CU_STREAM_WAIT_VALUE_FLUSH = 1 << 30
    } CUstreamWaitValue_flags;
    typedef enum CUstreamWriteValue_flags_enum {
        CU_STREAM_WRITE_VALUE_DEFAULT = 0x0,
        CU_STREAM_WRITE_VALUE_NO_MEMORY_BARRIER = 0x1
    } CUstreamWriteValue_flags;
    typedef enum CUstreamBatchMemOpType_enum {
        CU_STREAM_MEM_OP_WAIT_VALUE_32 = 1,
        CU_STREAM_MEM_OP_WRITE_VALUE_32 = 2,
        CU_STREAM_MEM_OP_WAIT_VALUE_64 = 4,
        CU_STREAM_MEM_OP_WRITE_VALUE_64 = 5,
        CU_STREAM_MEM_OP_FLUSH_REMOTE_WRITES = 3
    } CUstreamBatchMemOpType;
    typedef union CUstreamBatchMemOpParams_union {
        CUstreamBatchMemOpType operation;
        struct CUstreamMemOpWaitValueParams_st {
            CUstreamBatchMemOpType operation;
            CUdeviceptr address;
            union {
                cuuint32_t value;
                cuuint64_t value64;
            };
            unsigned int flags;
            CUdeviceptr alias;
        } waitValue;
        struct CUstreamMemOpWriteValueParams_st {
            CUstreamBatchMemOpType operation;
            CUdeviceptr address;
            union {
                cuuint32_t value;
                cuuint64_t value64;
            };
            unsigned int flags;
            CUdeviceptr alias;
        } writeValue;
        struct CUstreamMemOpFlushRemoteWritesParams_st {
            CUstreamBatchMemOpType operation;
            unsigned int flags;
        } flushRemoteWrites;
        cuuint64_t pad[6];
    } CUstreamBatchMemOpParams;
    typedef enum CUoccupancy_flags_enum {
        CU_OCCUPANCY_DEFAULT = 0x0,
        CU_OCCUPANCY_DISABLE_CACHING_OVERRIDE = 0x1
    } CUoccupancy_flags;
    typedef enum CUarray_format_enum {
        CU_AD_FORMAT_UNSIGNED_INT8 = 0x01,
        CU_AD_FORMAT_UNSIGNED_INT16 = 0x02,
        CU_AD_FORMAT_UNSIGNED_INT32 = 0x03,
        CU_AD_FORMAT_SIGNED_INT8 = 0x08,
        CU_AD_FORMAT_SIGNED_INT16 = 0x09,
        CU_AD_FORMAT_SIGNED_INT32 = 0x0a,
        CU_AD_FORMAT_HALF = 0x10,
        CU_AD_FORMAT_FLOAT = 0x20
    } CUarray_format;
    typedef enum CUaddress_mode_enum {
        CU_TR_ADDRESS_MODE_WRAP = 0,
        CU_TR_ADDRESS_MODE_CLAMP = 1,
        CU_TR_ADDRESS_MODE_MIRROR = 2,
        CU_TR_ADDRESS_MODE_BORDER = 3
    } CUaddress_mode;
    typedef enum CUfilter_mode_enum {
        CU_TR_FILTER_MODE_POINT = 0,
        CU_TR_FILTER_MODE_LINEAR = 1
    } CUfilter_mode;
    typedef enum CUdevice_attribute_enum {
        CU_DEVICE_ATTRIBUTE_MAX_THREADS_PER_BLOCK = 1,
        CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_X = 2,
        CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_Y = 3,
        CU_DEVICE_ATTRIBUTE_MAX_BLOCK_DIM_Z = 4,
        CU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_X = 5,
        CU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_Y = 6,
        CU_DEVICE_ATTRIBUTE_MAX_GRID_DIM_Z = 7,
        CU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_BLOCK = 8,
        CU_DEVICE_ATTRIBUTE_SHARED_MEMORY_PER_BLOCK = 8,
        CU_DEVICE_ATTRIBUTE_TOTAL_CONSTANT_MEMORY = 9,
        CU_DEVICE_ATTRIBUTE_WARP_SIZE = 10,
        CU_DEVICE_ATTRIBUTE_MAX_PITCH = 11,
        CU_DEVICE_ATTRIBUTE_MAX_REGISTERS_PER_BLOCK = 12,
        CU_DEVICE_ATTRIBUTE_REGISTERS_PER_BLOCK = 12,
        CU_DEVICE_ATTRIBUTE_CLOCK_RATE = 13,
        CU_DEVICE_ATTRIBUTE_TEXTURE_ALIGNMENT = 14,
        CU_DEVICE_ATTRIBUTE_GPU_OVERLAP = 15,
        CU_DEVICE_ATTRIBUTE_MULTIPROCESSOR_COUNT = 16,
        CU_DEVICE_ATTRIBUTE_KERNEL_EXEC_TIMEOUT = 17,
        CU_DEVICE_ATTRIBUTE_INTEGRATED = 18,
        CU_DEVICE_ATTRIBUTE_CAN_MAP_HOST_MEMORY = 19,
        CU_DEVICE_ATTRIBUTE_COMPUTE_MODE = 20,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_WIDTH = 21,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_WIDTH = 22,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_HEIGHT = 23,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_WIDTH = 24,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_HEIGHT = 25,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_DEPTH = 26,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_WIDTH = 27,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_HEIGHT = 28,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LAYERED_LAYERS = 29,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_ARRAY_WIDTH = 27,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_ARRAY_HEIGHT = 28,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_ARRAY_NUMSLICES = 29,
        CU_DEVICE_ATTRIBUTE_SURFACE_ALIGNMENT = 30,
        CU_DEVICE_ATTRIBUTE_CONCURRENT_KERNELS = 31,
        CU_DEVICE_ATTRIBUTE_ECC_ENABLED = 32,
        CU_DEVICE_ATTRIBUTE_PCI_BUS_ID = 33,
        CU_DEVICE_ATTRIBUTE_PCI_DEVICE_ID = 34,
        CU_DEVICE_ATTRIBUTE_TCC_DRIVER = 35,
        CU_DEVICE_ATTRIBUTE_MEMORY_CLOCK_RATE = 36,
        CU_DEVICE_ATTRIBUTE_GLOBAL_MEMORY_BUS_WIDTH = 37,
        CU_DEVICE_ATTRIBUTE_L2_CACHE_SIZE = 38,
        CU_DEVICE_ATTRIBUTE_MAX_THREADS_PER_MULTIPROCESSOR = 39,
        CU_DEVICE_ATTRIBUTE_ASYNC_ENGINE_COUNT = 40,
        CU_DEVICE_ATTRIBUTE_UNIFIED_ADDRESSING = 41,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_LAYERED_WIDTH = 42,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_LAYERED_LAYERS = 43,
        CU_DEVICE_ATTRIBUTE_CAN_TEX2D_GATHER = 44,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_GATHER_WIDTH = 45,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_GATHER_HEIGHT = 46,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_WIDTH_ALTERNATE = 47,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_HEIGHT_ALTERNATE = 48,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE3D_DEPTH_ALTERNATE = 49,
        CU_DEVICE_ATTRIBUTE_PCI_DOMAIN_ID = 50,
        CU_DEVICE_ATTRIBUTE_TEXTURE_PITCH_ALIGNMENT = 51,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURECUBEMAP_WIDTH = 52,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURECUBEMAP_LAYERED_WIDTH = 53,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURECUBEMAP_LAYERED_LAYERS = 54,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE1D_WIDTH = 55,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_WIDTH = 56,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_HEIGHT = 57,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE3D_WIDTH = 58,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE3D_HEIGHT = 59,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE3D_DEPTH = 60,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE1D_LAYERED_WIDTH = 61,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE1D_LAYERED_LAYERS = 62,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_LAYERED_WIDTH = 63,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_LAYERED_HEIGHT = 64,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACE2D_LAYERED_LAYERS = 65,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACECUBEMAP_WIDTH = 66,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACECUBEMAP_LAYERED_WIDTH = 67,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_SURFACECUBEMAP_LAYERED_LAYERS = 68,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_LINEAR_WIDTH = 69,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_WIDTH = 70,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_HEIGHT = 71,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_LINEAR_PITCH = 72,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_MIPMAPPED_WIDTH = 73,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE2D_MIPMAPPED_HEIGHT = 74,
        CU_DEVICE_ATTRIBUTE_COMPUTE_CAPABILITY_MAJOR = 75,
        CU_DEVICE_ATTRIBUTE_COMPUTE_CAPABILITY_MINOR = 76,
        CU_DEVICE_ATTRIBUTE_MAXIMUM_TEXTURE1D_MIPMAPPED_WIDTH = 77,
        CU_DEVICE_ATTRIBUTE_STREAM_PRIORITIES_SUPPORTED = 78,
        CU_DEVICE_ATTRIBUTE_GLOBAL_L1_CACHE_SUPPORTED = 79,
        CU_DEVICE_ATTRIBUTE_LOCAL_L1_CACHE_SUPPORTED = 80,
        CU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_MULTIPROCESSOR = 81,
        CU_DEVICE_ATTRIBUTE_MAX_REGISTERS_PER_MULTIPROCESSOR = 82,
        CU_DEVICE_ATTRIBUTE_MANAGED_MEMORY = 83,
        CU_DEVICE_ATTRIBUTE_MULTI_GPU_BOARD = 84,
        CU_DEVICE_ATTRIBUTE_MULTI_GPU_BOARD_GROUP_ID = 85,
        CU_DEVICE_ATTRIBUTE_HOST_NATIVE_ATOMIC_SUPPORTED = 86,
        CU_DEVICE_ATTRIBUTE_SINGLE_TO_DOUBLE_PRECISION_PERF_RATIO = 87,
        CU_DEVICE_ATTRIBUTE_PAGEABLE_MEMORY_ACCESS = 88,
        CU_DEVICE_ATTRIBUTE_CONCURRENT_MANAGED_ACCESS = 89,
        CU_DEVICE_ATTRIBUTE_COMPUTE_PREEMPTION_SUPPORTED = 90,
        CU_DEVICE_ATTRIBUTE_CAN_USE_HOST_POINTER_FOR_REGISTERED_MEM = 91,
        CU_DEVICE_ATTRIBUTE_CAN_USE_STREAM_MEM_OPS = 92,
        CU_DEVICE_ATTRIBUTE_CAN_USE_64_BIT_STREAM_MEM_OPS = 93,
        CU_DEVICE_ATTRIBUTE_CAN_USE_STREAM_WAIT_VALUE_NOR = 94,
        CU_DEVICE_ATTRIBUTE_COOPERATIVE_LAUNCH = 95,
        CU_DEVICE_ATTRIBUTE_COOPERATIVE_MULTI_DEVICE_LAUNCH = 96,
        CU_DEVICE_ATTRIBUTE_MAX_SHARED_MEMORY_PER_BLOCK_OPTIN = 97,
        CU_DEVICE_ATTRIBUTE_CAN_FLUSH_REMOTE_WRITES = 98,
        CU_DEVICE_ATTRIBUTE_HOST_REGISTER_SUPPORTED = 99,
        CU_DEVICE_ATTRIBUTE_PAGEABLE_MEMORY_ACCESS_USES_HOST_PAGE_TABLES = 100,
        CU_DEVICE_ATTRIBUTE_DIRECT_MANAGED_MEM_ACCESS_FROM_HOST = 101,
        CU_DEVICE_ATTRIBUTE_MAX
    } CUdevice_attribute;
    typedef struct CUdevprop_st {
        int maxThreadsPerBlock;
        int maxThreadsDim[3];
        int maxGridSize[3];
        int sharedMemPerBlock;
        int totalConstantMemory;
        int SIMDWidth;
        int memPitch;
        int regsPerBlock;
        int clockRate;
        int textureAlign;
    } CUdevprop;
    typedef enum CUpointer_attribute_enum {
        CU_POINTER_ATTRIBUTE_CONTEXT = 1,
        CU_POINTER_ATTRIBUTE_MEMORY_TYPE = 2,
        CU_POINTER_ATTRIBUTE_DEVICE_POINTER = 3,
        CU_POINTER_ATTRIBUTE_HOST_POINTER = 4,
        CU_POINTER_ATTRIBUTE_P2P_TOKENS = 5,
        CU_POINTER_ATTRIBUTE_SYNC_MEMOPS = 6,
        CU_POINTER_ATTRIBUTE_BUFFER_ID = 7,
        CU_POINTER_ATTRIBUTE_IS_MANAGED = 8,
        CU_POINTER_ATTRIBUTE_DEVICE_ORDINAL = 9
    } CUpointer_attribute;
    typedef enum CUfunction_attribute_enum {
        CU_FUNC_ATTRIBUTE_MAX_THREADS_PER_BLOCK = 0,
        CU_FUNC_ATTRIBUTE_SHARED_SIZE_BYTES = 1,
        CU_FUNC_ATTRIBUTE_CONST_SIZE_BYTES = 2,
        CU_FUNC_ATTRIBUTE_LOCAL_SIZE_BYTES = 3,
        CU_FUNC_ATTRIBUTE_NUM_REGS = 4,
        CU_FUNC_ATTRIBUTE_PTX_VERSION = 5,
        CU_FUNC_ATTRIBUTE_BINARY_VERSION = 6,
        CU_FUNC_ATTRIBUTE_CACHE_MODE_CA = 7,
        CU_FUNC_ATTRIBUTE_MAX_DYNAMIC_SHARED_SIZE_BYTES = 8,
        CU_FUNC_ATTRIBUTE_PREFERRED_SHARED_MEMORY_CARVEOUT = 9,
        CU_FUNC_ATTRIBUTE_MAX
    } CUfunction_attribute;
    typedef enum CUfunc_cache_enum {
        CU_FUNC_CACHE_PREFER_NONE = 0x00,
        CU_FUNC_CACHE_PREFER_SHARED = 0x01,
        CU_FUNC_CACHE_PREFER_L1 = 0x02,
        CU_FUNC_CACHE_PREFER_EQUAL = 0x03
    } CUfunc_cache;
    typedef enum CUsharedconfig_enum {
        CU_SHARED_MEM_CONFIG_DEFAULT_BANK_SIZE = 0x00,
        CU_SHARED_MEM_CONFIG_FOUR_BYTE_BANK_SIZE = 0x01,
        CU_SHARED_MEM_CONFIG_EIGHT_BYTE_BANK_SIZE = 0x02
    } CUsharedconfig;
    typedef enum CUshared_carveout_enum {
        CU_SHAREDMEM_CARVEOUT_DEFAULT = -1,
        CU_SHAREDMEM_CARVEOUT_MAX_SHARED = 100,
        CU_SHAREDMEM_CARVEOUT_MAX_L1 = 0
    } CUshared_carveout;
    typedef enum CUmemorytype_enum {
        CU_MEMORYTYPE_HOST = 0x01,
        CU_MEMORYTYPE_DEVICE = 0x02,
        CU_MEMORYTYPE_ARRAY = 0x03,
        CU_MEMORYTYPE_UNIFIED = 0x04
    } CUmemorytype;
    typedef enum CUcomputemode_enum {
        CU_COMPUTEMODE_DEFAULT = 0,
        CU_COMPUTEMODE_PROHIBITED = 2,
        CU_COMPUTEMODE_EXCLUSIVE_PROCESS = 3
    } CUcomputemode;
    typedef enum CUmem_advise_enum {
        CU_MEM_ADVISE_SET_READ_MOSTLY = 1,
        CU_MEM_ADVISE_UNSET_READ_MOSTLY = 2,
        CU_MEM_ADVISE_SET_PREFERRED_LOCATION = 3,
        CU_MEM_ADVISE_UNSET_PREFERRED_LOCATION = 4,
        CU_MEM_ADVISE_SET_ACCESSED_BY = 5,
        CU_MEM_ADVISE_UNSET_ACCESSED_BY = 6
    } CUmem_advise;
    typedef enum CUmem_range_attribute_enum {
        CU_MEM_RANGE_ATTRIBUTE_READ_MOSTLY = 1,
        CU_MEM_RANGE_ATTRIBUTE_PREFERRED_LOCATION = 2,
        CU_MEM_RANGE_ATTRIBUTE_ACCESSED_BY = 3,
        CU_MEM_RANGE_ATTRIBUTE_LAST_PREFETCH_LOCATION = 4
    } CUmem_range_attribute;
    typedef enum CUjit_option_enum
    {
        CU_JIT_MAX_REGISTERS = 0,
        CU_JIT_THREADS_PER_BLOCK,
        CU_JIT_WALL_TIME,
        CU_JIT_INFO_LOG_BUFFER,
        CU_JIT_INFO_LOG_BUFFER_SIZE_BYTES,
        CU_JIT_ERROR_LOG_BUFFER,
        CU_JIT_ERROR_LOG_BUFFER_SIZE_BYTES,
        CU_JIT_OPTIMIZATION_LEVEL,
        CU_JIT_TARGET_FROM_CUCONTEXT,
        CU_JIT_TARGET,
        CU_JIT_FALLBACK_STRATEGY,
        CU_JIT_GENERATE_DEBUG_INFO,
        CU_JIT_LOG_VERBOSE,
        CU_JIT_GENERATE_LINE_INFO,
        CU_JIT_CACHE_MODE,
        CU_JIT_NEW_SM3X_OPT,
        CU_JIT_FAST_COMPILE,
        CU_JIT_GLOBAL_SYMBOL_NAMES,
        CU_JIT_GLOBAL_SYMBOL_ADDRESSES,
        CU_JIT_GLOBAL_SYMBOL_COUNT,
        CU_JIT_NUM_OPTIONS
    } CUjit_option;
    typedef enum CUjit_target_enum
    {
        CU_TARGET_COMPUTE_20 = 20,
        CU_TARGET_COMPUTE_21 = 21,
        CU_TARGET_COMPUTE_30 = 30,
        CU_TARGET_COMPUTE_32 = 32,
        CU_TARGET_COMPUTE_35 = 35,
        CU_TARGET_COMPUTE_37 = 37,
        CU_TARGET_COMPUTE_50 = 50,
        CU_TARGET_COMPUTE_52 = 52,
        CU_TARGET_COMPUTE_53 = 53,
        CU_TARGET_COMPUTE_60 = 60,
        CU_TARGET_COMPUTE_61 = 61,
        CU_TARGET_COMPUTE_62 = 62,
        CU_TARGET_COMPUTE_70 = 70,
        CU_TARGET_COMPUTE_75 = 75
    } CUjit_target;
    typedef enum CUjit_fallback_enum
    {
        CU_PREFER_PTX = 0,
        CU_PREFER_BINARY
    } CUjit_fallback;
    typedef enum CUjit_cacheMode_enum
    {
        CU_JIT_CACHE_OPTION_NONE = 0,
        CU_JIT_CACHE_OPTION_CG,
        CU_JIT_CACHE_OPTION_CA
    } CUjit_cacheMode;
    typedef enum CUjitInputType_enum
    {
        CU_JIT_INPUT_CUBIN = 0,
        CU_JIT_INPUT_PTX,
        CU_JIT_INPUT_FATBINARY,
        CU_JIT_INPUT_OBJECT,
        CU_JIT_INPUT_LIBRARY,
        CU_JIT_NUM_INPUT_TYPES
    } CUjitInputType;
    typedef struct CUlinkState_st *CUlinkState;
    typedef enum CUgraphicsRegisterFlags_enum {
        CU_GRAPHICS_REGISTER_FLAGS_NONE = 0x00,
        CU_GRAPHICS_REGISTER_FLAGS_READ_ONLY = 0x01,
        CU_GRAPHICS_REGISTER_FLAGS_WRITE_DISCARD = 0x02,
        CU_GRAPHICS_REGISTER_FLAGS_SURFACE_LDST = 0x04,
        CU_GRAPHICS_REGISTER_FLAGS_TEXTURE_GATHER = 0x08
    } CUgraphicsRegisterFlags;
    typedef enum CUgraphicsMapResourceFlags_enum {
        CU_GRAPHICS_MAP_RESOURCE_FLAGS_NONE = 0x00,
        CU_GRAPHICS_MAP_RESOURCE_FLAGS_READ_ONLY = 0x01,
        CU_GRAPHICS_MAP_RESOURCE_FLAGS_WRITE_DISCARD = 0x02
    } CUgraphicsMapResourceFlags;
    typedef enum CUarray_cubemap_face_enum {
        CU_CUBEMAP_FACE_POSITIVE_X = 0x00,
        CU_CUBEMAP_FACE_NEGATIVE_X = 0x01,
        CU_CUBEMAP_FACE_POSITIVE_Y = 0x02,
        CU_CUBEMAP_FACE_NEGATIVE_Y = 0x03,
        CU_CUBEMAP_FACE_POSITIVE_Z = 0x04,
        CU_CUBEMAP_FACE_NEGATIVE_Z = 0x05
    } CUarray_cubemap_face;
    typedef enum CUlimit_enum {
        CU_LIMIT_STACK_SIZE = 0x00,
        CU_LIMIT_PRINTF_FIFO_SIZE = 0x01,
        CU_LIMIT_MALLOC_HEAP_SIZE = 0x02,
        CU_LIMIT_DEV_RUNTIME_SYNC_DEPTH = 0x03,
        CU_LIMIT_DEV_RUNTIME_PENDING_LAUNCH_COUNT = 0x04,
        CU_LIMIT_MAX_L2_FETCH_GRANULARITY = 0x05,
        CU_LIMIT_MAX
    } CUlimit;
    typedef enum CUresourcetype_enum {
        CU_RESOURCE_TYPE_ARRAY = 0x00,
        CU_RESOURCE_TYPE_MIPMAPPED_ARRAY = 0x01,
        CU_RESOURCE_TYPE_LINEAR = 0x02,
        CU_RESOURCE_TYPE_PITCH2D = 0x03
    } CUresourcetype;
    typedef void(__stdcall *CUhostFn)(void *userData);
    typedef struct CUDA_KERNEL_NODE_PARAMS_st {
        CUfunction func;
        unsigned int gridDimX;
        unsigned int gridDimY;
        unsigned int gridDimZ;
        unsigned int blockDimX;
        unsigned int blockDimY;
        unsigned int blockDimZ;
        unsigned int sharedMemBytes;
        void **kernelParams;
        void **extra;
    } CUDA_KERNEL_NODE_PARAMS;
    typedef struct CUDA_MEMSET_NODE_PARAMS_st {
        CUdeviceptr dst;
        size_t pitch;
        unsigned int value;
        unsigned int elementSize;
        size_t width;
        size_t height;
    } CUDA_MEMSET_NODE_PARAMS;
    typedef struct CUDA_HOST_NODE_PARAMS_st {
        CUhostFn fn;
        void *userData;
    } CUDA_HOST_NODE_PARAMS;
    typedef enum CUgraphNodeType_enum {
        CU_GRAPH_NODE_TYPE_KERNEL = 0,
        CU_GRAPH_NODE_TYPE_MEMCPY = 1,
        CU_GRAPH_NODE_TYPE_MEMSET = 2,
        CU_GRAPH_NODE_TYPE_HOST = 3,
        CU_GRAPH_NODE_TYPE_GRAPH = 4,
        CU_GRAPH_NODE_TYPE_EMPTY = 5,
        CU_GRAPH_NODE_TYPE_COUNT
    } CUgraphNodeType;
    typedef enum CUstreamCaptureStatus_enum {
        CU_STREAM_CAPTURE_STATUS_NONE = 0,
        CU_STREAM_CAPTURE_STATUS_ACTIVE = 1,
        CU_STREAM_CAPTURE_STATUS_INVALIDATED = 2
    } CUstreamCaptureStatus;
    typedef enum cudaError_enum {
        CUDA_SUCCESS = 0,
        CUDA_ERROR_INVALID_VALUE = 1,
        CUDA_ERROR_OUT_OF_MEMORY = 2,
        CUDA_ERROR_NOT_INITIALIZED = 3,
        CUDA_ERROR_DEINITIALIZED = 4,
        CUDA_ERROR_PROFILER_DISABLED = 5,
        CUDA_ERROR_PROFILER_NOT_INITIALIZED = 6,
        CUDA_ERROR_PROFILER_ALREADY_STARTED = 7,
        CUDA_ERROR_PROFILER_ALREADY_STOPPED = 8,
        CUDA_ERROR_NO_DEVICE = 100,
        CUDA_ERROR_INVALID_DEVICE = 101,
        CUDA_ERROR_INVALID_IMAGE = 200,
        CUDA_ERROR_INVALID_CONTEXT = 201,
        CUDA_ERROR_CONTEXT_ALREADY_CURRENT = 202,
        CUDA_ERROR_MAP_FAILED = 205,
        CUDA_ERROR_UNMAP_FAILED = 206,
        CUDA_ERROR_ARRAY_IS_MAPPED = 207,
        CUDA_ERROR_ALREADY_MAPPED = 208,
        CUDA_ERROR_NO_BINARY_FOR_GPU = 209,
        CUDA_ERROR_ALREADY_ACQUIRED = 210,
        CUDA_ERROR_NOT_MAPPED = 211,
        CUDA_ERROR_NOT_MAPPED_AS_ARRAY = 212,
        CUDA_ERROR_NOT_MAPPED_AS_POINTER = 213,
        CUDA_ERROR_ECC_UNCORRECTABLE = 214,
        CUDA_ERROR_UNSUPPORTED_LIMIT = 215,
        CUDA_ERROR_CONTEXT_ALREADY_IN_USE = 216,
        CUDA_ERROR_PEER_ACCESS_UNSUPPORTED = 217,
        CUDA_ERROR_INVALID_PTX = 218,
        CUDA_ERROR_INVALID_GRAPHICS_CONTEXT = 219,
        CUDA_ERROR_NVLINK_UNCORRECTABLE = 220,
        CUDA_ERROR_JIT_COMPILER_NOT_FOUND = 221,
        CUDA_ERROR_INVALID_SOURCE = 300,
        CUDA_ERROR_FILE_NOT_FOUND = 301,
        CUDA_ERROR_SHARED_OBJECT_SYMBOL_NOT_FOUND = 302,
        CUDA_ERROR_SHARED_OBJECT_INIT_FAILED = 303,
        CUDA_ERROR_OPERATING_SYSTEM = 304,
        CUDA_ERROR_INVALID_HANDLE = 400,
        CUDA_ERROR_ILLEGAL_STATE = 401,
        CUDA_ERROR_NOT_FOUND = 500,
        CUDA_ERROR_NOT_READY = 600,
        CUDA_ERROR_ILLEGAL_ADDRESS = 700,
        CUDA_ERROR_LAUNCH_OUT_OF_RESOURCES = 701,
        CUDA_ERROR_LAUNCH_TIMEOUT = 702,
        CUDA_ERROR_LAUNCH_INCOMPATIBLE_TEXTURING = 703,
        CUDA_ERROR_PEER_ACCESS_ALREADY_ENABLED = 704,
        CUDA_ERROR_PEER_ACCESS_NOT_ENABLED = 705,
        CUDA_ERROR_PRIMARY_CONTEXT_ACTIVE = 708,
        CUDA_ERROR_CONTEXT_IS_DESTROYED = 709,
        CUDA_ERROR_ASSERT = 710,
        CUDA_ERROR_TOO_MANY_PEERS = 711,
        CUDA_ERROR_HOST_MEMORY_ALREADY_REGISTERED = 712,
        CUDA_ERROR_HOST_MEMORY_NOT_REGISTERED = 713,
        CUDA_ERROR_HARDWARE_STACK_ERROR = 714,
        CUDA_ERROR_ILLEGAL_INSTRUCTION = 715,
        CUDA_ERROR_MISALIGNED_ADDRESS = 716,
        CUDA_ERROR_INVALID_ADDRESS_SPACE = 717,
        CUDA_ERROR_INVALID_PC = 718,
        CUDA_ERROR_LAUNCH_FAILED = 719,
        CUDA_ERROR_COOPERATIVE_LAUNCH_TOO_LARGE = 720,
        CUDA_ERROR_NOT_PERMITTED = 800,
        CUDA_ERROR_NOT_SUPPORTED = 801,
        CUDA_ERROR_SYSTEM_NOT_READY = 802,
        CUDA_ERROR_STREAM_CAPTURE_UNSUPPORTED = 900,
        CUDA_ERROR_STREAM_CAPTURE_INVALIDATED = 901,
        CUDA_ERROR_STREAM_CAPTURE_MERGE = 902,
        CUDA_ERROR_STREAM_CAPTURE_UNMATCHED = 903,
        CUDA_ERROR_STREAM_CAPTURE_UNJOINED = 904,
        CUDA_ERROR_STREAM_CAPTURE_ISOLATION = 905,
        CUDA_ERROR_STREAM_CAPTURE_IMPLICIT = 906,
        CUDA_ERROR_CAPTURED_EVENT = 907,
        CUDA_ERROR_UNKNOWN = 999
    } CUresult;
    typedef enum CUdevice_P2PAttribute_enum {
        CU_DEVICE_P2P_ATTRIBUTE_PERFORMANCE_RANK = 0x01,
        CU_DEVICE_P2P_ATTRIBUTE_ACCESS_SUPPORTED = 0x02,
        CU_DEVICE_P2P_ATTRIBUTE_NATIVE_ATOMIC_SUPPORTED = 0x03,
        CU_DEVICE_P2P_ATTRIBUTE_ARRAY_ACCESS_ACCESS_SUPPORTED = 0x04,
        CU_DEVICE_P2P_ATTRIBUTE_CUDA_ARRAY_ACCESS_SUPPORTED = 0x04
    } CUdevice_P2PAttribute;
    typedef void(__stdcall *CUstreamCallback)(CUstream hStream, CUresult status, void *userData);
    typedef size_t(__stdcall *CUoccupancyB2DSize)(int blockSize);
    typedef struct CUDA_MEMCPY2D_st {
        size_t srcXInBytes;
        size_t srcY;
        CUmemorytype srcMemoryType;
        const void *srcHost;
        CUdeviceptr srcDevice;
        CUarray srcArray;
        size_t srcPitch;
        size_t dstXInBytes;
        size_t dstY;
        CUmemorytype dstMemoryType;
        void *dstHost;
        CUdeviceptr dstDevice;
        CUarray dstArray;
        size_t dstPitch;
        size_t WidthInBytes;
        size_t Height;
    } CUDA_MEMCPY2D;
    typedef struct CUDA_MEMCPY3D_st {
        size_t srcXInBytes;
        size_t srcY;
        size_t srcZ;
        size_t srcLOD;
        CUmemorytype srcMemoryType;
        const void *srcHost;
        CUdeviceptr srcDevice;
        CUarray srcArray;
        void *reserved0;
        size_t srcPitch;
        size_t srcHeight;
        size_t dstXInBytes;
        size_t dstY;
        size_t dstZ;
        size_t dstLOD;
        CUmemorytype dstMemoryType;
        void *dstHost;
        CUdeviceptr dstDevice;
        CUarray dstArray;
        void *reserved1;
        size_t dstPitch;
        size_t dstHeight;
        size_t WidthInBytes;
        size_t Height;
        size_t Depth;
    } CUDA_MEMCPY3D;
    typedef struct CUDA_MEMCPY3D_PEER_st {
        size_t srcXInBytes;
        size_t srcY;
        size_t srcZ;
        size_t srcLOD;
        CUmemorytype srcMemoryType;
        const void *srcHost;
        CUdeviceptr srcDevice;
        CUarray srcArray;
        CUcontext srcContext;
        size_t srcPitch;
        size_t srcHeight;
        size_t dstXInBytes;
        size_t dstY;
        size_t dstZ;
        size_t dstLOD;
        CUmemorytype dstMemoryType;
        void *dstHost;
        CUdeviceptr dstDevice;
        CUarray dstArray;
        CUcontext dstContext;
        size_t dstPitch;
        size_t dstHeight;
        size_t WidthInBytes;
        size_t Height;
        size_t Depth;
    } CUDA_MEMCPY3D_PEER;
    typedef struct CUDA_ARRAY_DESCRIPTOR_st
    {
        size_t Width;
        size_t Height;
        CUarray_format Format;
        unsigned int NumChannels;
    } CUDA_ARRAY_DESCRIPTOR;
    typedef struct CUDA_ARRAY3D_DESCRIPTOR_st
    {
        size_t Width;
        size_t Height;
        size_t Depth;
        CUarray_format Format;
        unsigned int NumChannels;
        unsigned int Flags;
    } CUDA_ARRAY3D_DESCRIPTOR;
    typedef struct CUDA_RESOURCE_DESC_st
    {
        CUresourcetype resType;
        union {
            struct {
                CUarray hArray;
            } array;
            struct {
                CUmipmappedArray hMipmappedArray;
            } mipmap;
            struct {
                CUdeviceptr devPtr;
                CUarray_format format;
                unsigned int numChannels;
                size_t sizeInBytes;
            } linear;
            struct {
                CUdeviceptr devPtr;
                CUarray_format format;
                unsigned int numChannels;
                size_t width;
                size_t height;
                size_t pitchInBytes;
            } pitch2D;
            struct {
                int reserved[32];
            } reserved;
        } res;
        unsigned int flags;
    } CUDA_RESOURCE_DESC;
    typedef struct CUDA_TEXTURE_DESC_st {
        CUaddress_mode addressMode[3];
        CUfilter_mode filterMode;
        unsigned int flags;
        unsigned int maxAnisotropy;
        CUfilter_mode mipmapFilterMode;
        float mipmapLevelBias;
        float minMipmapLevelClamp;
        float maxMipmapLevelClamp;
        float borderColor[4];
        int reserved[12];
    } CUDA_TEXTURE_DESC;
    typedef enum CUresourceViewFormat_enum
    {
        CU_RES_VIEW_FORMAT_NONE = 0x00,
        CU_RES_VIEW_FORMAT_UINT_1X8 = 0x01,
        CU_RES_VIEW_FORMAT_UINT_2X8 = 0x02,
        CU_RES_VIEW_FORMAT_UINT_4X8 = 0x03,
        CU_RES_VIEW_FORMAT_SINT_1X8 = 0x04,
        CU_RES_VIEW_FORMAT_SINT_2X8 = 0x05,
        CU_RES_VIEW_FORMAT_SINT_4X8 = 0x06,
        CU_RES_VIEW_FORMAT_UINT_1X16 = 0x07,
        CU_RES_VIEW_FORMAT_UINT_2X16 = 0x08,
        CU_RES_VIEW_FORMAT_UINT_4X16 = 0x09,
        CU_RES_VIEW_FORMAT_SINT_1X16 = 0x0a,
        CU_RES_VIEW_FORMAT_SINT_2X16 = 0x0b,
        CU_RES_VIEW_FORMAT_SINT_4X16 = 0x0c,
        CU_RES_VIEW_FORMAT_UINT_1X32 = 0x0d,
        CU_RES_VIEW_FORMAT_UINT_2X32 = 0x0e,
        CU_RES_VIEW_FORMAT_UINT_4X32 = 0x0f,
        CU_RES_VIEW_FORMAT_SINT_1X32 = 0x10,
        CU_RES_VIEW_FORMAT_SINT_2X32 = 0x11,
        CU_RES_VIEW_FORMAT_SINT_4X32 = 0x12,
        CU_RES_VIEW_FORMAT_FLOAT_1X16 = 0x13,
        CU_RES_VIEW_FORMAT_FLOAT_2X16 = 0x14,
        CU_RES_VIEW_FORMAT_FLOAT_4X16 = 0x15,
        CU_RES_VIEW_FORMAT_FLOAT_1X32 = 0x16,
        CU_RES_VIEW_FORMAT_FLOAT_2X32 = 0x17,
        CU_RES_VIEW_FORMAT_FLOAT_4X32 = 0x18,
        CU_RES_VIEW_FORMAT_UNSIGNED_BC1 = 0x19,
        CU_RES_VIEW_FORMAT_UNSIGNED_BC2 = 0x1a,
        CU_RES_VIEW_FORMAT_UNSIGNED_BC3 = 0x1b,
        CU_RES_VIEW_FORMAT_UNSIGNED_BC4 = 0x1c,
        CU_RES_VIEW_FORMAT_SIGNED_BC4 = 0x1d,
        CU_RES_VIEW_FORMAT_UNSIGNED_BC5 = 0x1e,
        CU_RES_VIEW_FORMAT_SIGNED_BC5 = 0x1f,
        CU_RES_VIEW_FORMAT_UNSIGNED_BC6H = 0x20,
        CU_RES_VIEW_FORMAT_SIGNED_BC6H = 0x21,
        CU_RES_VIEW_FORMAT_UNSIGNED_BC7 = 0x22
    } CUresourceViewFormat;
    typedef struct CUDA_RESOURCE_VIEW_DESC_st
    {
        CUresourceViewFormat format;
        size_t width;
        size_t height;
        size_t depth;
        unsigned int firstMipmapLevel;
        unsigned int lastMipmapLevel;
        unsigned int firstLayer;
        unsigned int lastLayer;
        unsigned int reserved[16];
    } CUDA_RESOURCE_VIEW_DESC;
    typedef struct CUDA_POINTER_ATTRIBUTE_P2P_TOKENS_st {
        unsigned long long p2pToken;
        unsigned int vaSpaceToken;
    } CUDA_POINTER_ATTRIBUTE_P2P_TOKENS;
    typedef struct CUDA_LAUNCH_PARAMS_st {
        CUfunction function;
        unsigned int gridDimX;
        unsigned int gridDimY;
        unsigned int gridDimZ;
        unsigned int blockDimX;
        unsigned int blockDimY;
        unsigned int blockDimZ;
        unsigned int sharedMemBytes;
        CUstream hStream;
        void **kernelParams;
    } CUDA_LAUNCH_PARAMS;
    typedef enum CUexternalMemoryHandleType_enum {
        CU_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD = 1,
        CU_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32 = 2,
        CU_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_WIN32_KMT = 3,
        CU_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_HEAP = 4,
        CU_EXTERNAL_MEMORY_HANDLE_TYPE_D3D12_RESOURCE = 5
    } CUexternalMemoryHandleType;
    typedef struct CUDA_EXTERNAL_MEMORY_HANDLE_DESC_st {
        CUexternalMemoryHandleType type;
        union {
            int fd;
            struct {
                void *handle;
                const void *name;
            } win32;
        } handle;
        unsigned long long size;
        unsigned int flags;
        unsigned int reserved[16];
    } CUDA_EXTERNAL_MEMORY_HANDLE_DESC;
    typedef struct CUDA_EXTERNAL_MEMORY_BUFFER_DESC_st {
        unsigned long long offset;
        unsigned long long size;
        unsigned int flags;
        unsigned int reserved[16];
    } CUDA_EXTERNAL_MEMORY_BUFFER_DESC;
    typedef struct CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC_st {
        unsigned long long offset;
        CUDA_ARRAY3D_DESCRIPTOR arrayDesc;
        unsigned int numLevels;
        unsigned int reserved[16];
    } CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC;
    typedef enum CUexternalSemaphoreHandleType_enum {
        CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD = 1,
        CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32 = 2,
        CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_KMT = 3,
        CU_EXTERNAL_SEMAPHORE_HANDLE_TYPE_D3D12_FENCE = 4
    } CUexternalSemaphoreHandleType;
    typedef struct CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC_st {
        CUexternalSemaphoreHandleType type;
        union {
            int fd;
            struct {
                void *handle;
                const void *name;
            } win32;
        } handle;
        unsigned int flags;
        unsigned int reserved[16];
    } CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC;
    typedef struct CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS_st {
        struct {
            struct {
                unsigned long long value;
            } fence;
            unsigned int reserved[16];
        } params;
        unsigned int flags;
        unsigned int reserved[16];
    } CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS;
    typedef struct CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS_st {
        struct {
            struct {
                unsigned long long value;
            } fence;
            unsigned int reserved[16];
        } params;
        unsigned int flags;
        unsigned int reserved[16];
    } CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS;
    CUresult __stdcall cuGetErrorString(CUresult error, const char **pStr);
    CUresult __stdcall cuGetErrorName(CUresult error, const char **pStr);
    CUresult __stdcall cuInit(unsigned int Flags);
    CUresult __stdcall cuDriverGetVersion(int *driverVersion);
    CUresult __stdcall cuDeviceGet(CUdevice *device, int ordinal);
    CUresult __stdcall cuDeviceGetCount(int *count);
    CUresult __stdcall cuDeviceGetName(char *name, int len, CUdevice dev);
    CUresult __stdcall cuDeviceGetUuid(CUuuid *uuid, CUdevice dev);
    CUresult __stdcall cuDeviceGetLuid(char *luid, unsigned int *deviceNodeMask, CUdevice dev);
    CUresult __stdcall cuDeviceTotalMem_v2(size_t *bytes, CUdevice dev);
    CUresult __stdcall cuDeviceGetAttribute(int *pi, CUdevice_attribute attrib, CUdevice dev);
    __declspec(deprecated) CUresult __stdcall cuDeviceGetProperties(CUdevprop *prop, CUdevice dev);
    __declspec(deprecated) CUresult __stdcall cuDeviceComputeCapability(int *major, int *minor, CUdevice dev);
    CUresult __stdcall cuDevicePrimaryCtxRetain(CUcontext *pctx, CUdevice dev);
    CUresult __stdcall cuDevicePrimaryCtxRelease(CUdevice dev);
    CUresult __stdcall cuDevicePrimaryCtxSetFlags(CUdevice dev, unsigned int flags);
    CUresult __stdcall cuDevicePrimaryCtxGetState(CUdevice dev, unsigned int *flags, int *active);
    CUresult __stdcall cuDevicePrimaryCtxReset(CUdevice dev);
    CUresult __stdcall cuCtxCreate_v2(CUcontext *pctx, unsigned int flags, CUdevice dev);
    CUresult __stdcall cuCtxDestroy_v2(CUcontext ctx);
    CUresult __stdcall cuCtxPushCurrent_v2(CUcontext ctx);
    CUresult __stdcall cuCtxPopCurrent_v2(CUcontext *pctx);
    CUresult __stdcall cuCtxSetCurrent(CUcontext ctx);
    CUresult __stdcall cuCtxGetCurrent(CUcontext *pctx);
    CUresult __stdcall cuCtxGetDevice(CUdevice *device);
    CUresult __stdcall cuCtxGetFlags(unsigned int *flags);
    CUresult __stdcall cuCtxSynchronize(void);
    CUresult __stdcall cuCtxSetLimit(CUlimit limit, size_t value);
    CUresult __stdcall cuCtxGetLimit(size_t *pvalue, CUlimit limit);
    CUresult __stdcall cuCtxGetCacheConfig(CUfunc_cache *pconfig);
    CUresult __stdcall cuCtxSetCacheConfig(CUfunc_cache config);
    CUresult __stdcall cuCtxGetSharedMemConfig(CUsharedconfig *pConfig);
    CUresult __stdcall cuCtxSetSharedMemConfig(CUsharedconfig config);
    CUresult __stdcall cuCtxGetApiVersion(CUcontext ctx, unsigned int *version);
    CUresult __stdcall cuCtxGetStreamPriorityRange(int *leastPriority, int *greatestPriority);
    __declspec(deprecated) CUresult __stdcall cuCtxAttach(CUcontext *pctx, unsigned int flags);
    __declspec(deprecated) CUresult __stdcall cuCtxDetach(CUcontext ctx);
    CUresult __stdcall cuModuleLoad(CUmodule *module, const char *fname);
    CUresult __stdcall cuModuleLoadData(CUmodule *module, const void *image);
    CUresult __stdcall cuModuleLoadDataEx(CUmodule *module, const void *image, unsigned int numOptions, CUjit_option *options, void **optionValues);
    CUresult __stdcall cuModuleLoadFatBinary(CUmodule *module, const void *fatCubin);
    CUresult __stdcall cuModuleUnload(CUmodule hmod);
    CUresult __stdcall cuModuleGetFunction(CUfunction *hfunc, CUmodule hmod, const char *name);
    CUresult __stdcall cuModuleGetGlobal_v2(CUdeviceptr *dptr, size_t *bytes, CUmodule hmod, const char *name);
    CUresult __stdcall cuModuleGetTexRef(CUtexref *pTexRef, CUmodule hmod, const char *name);
    CUresult __stdcall cuModuleGetSurfRef(CUsurfref *pSurfRef, CUmodule hmod, const char *name);
    CUresult __stdcall cuLinkCreate_v2(unsigned int numOptions, CUjit_option *options, void **optionValues, CUlinkState *stateOut);
    CUresult __stdcall cuLinkAddData_v2(CUlinkState state, CUjitInputType type, void *data, size_t size, const char *name, unsigned int numOptions, CUjit_option *options, void **optionValues);
    CUresult __stdcall cuLinkAddFile_v2(CUlinkState state, CUjitInputType type, const char *path, unsigned int numOptions, CUjit_option *options, void **optionValues);
    CUresult __stdcall cuLinkComplete(CUlinkState state, void **cubinOut, size_t *sizeOut);
    CUresult __stdcall cuLinkDestroy(CUlinkState state);
    CUresult __stdcall cuMemGetInfo_v2(size_t *free, size_t *total);
    CUresult __stdcall cuMemAlloc_v2(CUdeviceptr *dptr, size_t bytesize);
    CUresult __stdcall cuMemAllocPitch_v2(CUdeviceptr *dptr, size_t *pPitch, size_t WidthInBytes, size_t Height, unsigned int ElementSizeBytes);
    CUresult __stdcall cuMemFree_v2(CUdeviceptr dptr);
    CUresult __stdcall cuMemGetAddressRange_v2(CUdeviceptr *pbase, size_t *psize, CUdeviceptr dptr);
    CUresult __stdcall cuMemAllocHost_v2(void **pp, size_t bytesize);
    CUresult __stdcall cuMemFreeHost(void *p);
    CUresult __stdcall cuMemHostAlloc(void **pp, size_t bytesize, unsigned int Flags);
    CUresult __stdcall cuMemHostGetDevicePointer_v2(CUdeviceptr *pdptr, void *p, unsigned int Flags);
    CUresult __stdcall cuMemHostGetFlags(unsigned int *pFlags, void *p);
    CUresult __stdcall cuMemAllocManaged(CUdeviceptr *dptr, size_t bytesize, unsigned int flags);
    CUresult __stdcall cuDeviceGetByPCIBusId(CUdevice *dev, const char *pciBusId);
    CUresult __stdcall cuDeviceGetPCIBusId(char *pciBusId, int len, CUdevice dev);
    CUresult __stdcall cuIpcGetEventHandle(CUipcEventHandle *pHandle, CUevent event);
    CUresult __stdcall cuIpcOpenEventHandle(CUevent *phEvent, CUipcEventHandle handle);
    CUresult __stdcall cuIpcGetMemHandle(CUipcMemHandle *pHandle, CUdeviceptr dptr);
    CUresult __stdcall cuIpcOpenMemHandle(CUdeviceptr *pdptr, CUipcMemHandle handle, unsigned int Flags);
    CUresult __stdcall cuIpcCloseMemHandle(CUdeviceptr dptr);
    CUresult __stdcall cuMemHostRegister_v2(void *p, size_t bytesize, unsigned int Flags);
    CUresult __stdcall cuMemHostUnregister(void *p);
    CUresult __stdcall cuMemcpy(CUdeviceptr dst, CUdeviceptr src, size_t ByteCount);
    CUresult __stdcall cuMemcpyPeer(CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount);
    CUresult __stdcall cuMemcpyHtoD_v2(CUdeviceptr dstDevice, const void *srcHost, size_t ByteCount);
    CUresult __stdcall cuMemcpyDtoH_v2(void *dstHost, CUdeviceptr srcDevice, size_t ByteCount);
    CUresult __stdcall cuMemcpyDtoD_v2(CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount);
    CUresult __stdcall cuMemcpyDtoA_v2(CUarray dstArray, size_t dstOffset, CUdeviceptr srcDevice, size_t ByteCount);
    CUresult __stdcall cuMemcpyAtoD_v2(CUdeviceptr dstDevice, CUarray srcArray, size_t srcOffset, size_t ByteCount);
    CUresult __stdcall cuMemcpyHtoA_v2(CUarray dstArray, size_t dstOffset, const void *srcHost, size_t ByteCount);
    CUresult __stdcall cuMemcpyAtoH_v2(void *dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount);
    CUresult __stdcall cuMemcpyAtoA_v2(CUarray dstArray, size_t dstOffset, CUarray srcArray, size_t srcOffset, size_t ByteCount);
    CUresult __stdcall cuMemcpy2D_v2(const CUDA_MEMCPY2D *pCopy);
    CUresult __stdcall cuMemcpy2DUnaligned_v2(const CUDA_MEMCPY2D *pCopy);
    CUresult __stdcall cuMemcpy3D_v2(const CUDA_MEMCPY3D *pCopy);
    CUresult __stdcall cuMemcpy3DPeer(const CUDA_MEMCPY3D_PEER *pCopy);
    CUresult __stdcall cuMemcpyAsync(CUdeviceptr dst, CUdeviceptr src, size_t ByteCount, CUstream hStream);
    CUresult __stdcall cuMemcpyPeerAsync(CUdeviceptr dstDevice, CUcontext dstContext, CUdeviceptr srcDevice, CUcontext srcContext, size_t ByteCount, CUstream hStream);
    CUresult __stdcall cuMemcpyHtoDAsync_v2(CUdeviceptr dstDevice, const void *srcHost, size_t ByteCount, CUstream hStream);
    CUresult __stdcall cuMemcpyDtoHAsync_v2(void *dstHost, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream);
    CUresult __stdcall cuMemcpyDtoDAsync_v2(CUdeviceptr dstDevice, CUdeviceptr srcDevice, size_t ByteCount, CUstream hStream);
    CUresult __stdcall cuMemcpyHtoAAsync_v2(CUarray dstArray, size_t dstOffset, const void *srcHost, size_t ByteCount, CUstream hStream);
    CUresult __stdcall cuMemcpyAtoHAsync_v2(void *dstHost, CUarray srcArray, size_t srcOffset, size_t ByteCount, CUstream hStream);
    CUresult __stdcall cuMemcpy2DAsync_v2(const CUDA_MEMCPY2D *pCopy, CUstream hStream);
    CUresult __stdcall cuMemcpy3DAsync_v2(const CUDA_MEMCPY3D *pCopy, CUstream hStream);
    CUresult __stdcall cuMemcpy3DPeerAsync(const CUDA_MEMCPY3D_PEER *pCopy, CUstream hStream);
    CUresult __stdcall cuMemsetD8_v2(CUdeviceptr dstDevice, unsigned char uc, size_t N);
    CUresult __stdcall cuMemsetD16_v2(CUdeviceptr dstDevice, unsigned short us, size_t N);
    CUresult __stdcall cuMemsetD32_v2(CUdeviceptr dstDevice, unsigned int ui, size_t N);
    CUresult __stdcall cuMemsetD2D8_v2(CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height);
    CUresult __stdcall cuMemsetD2D16_v2(CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height);
    CUresult __stdcall cuMemsetD2D32_v2(CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height);
    CUresult __stdcall cuMemsetD8Async(CUdeviceptr dstDevice, unsigned char uc, size_t N, CUstream hStream);
    CUresult __stdcall cuMemsetD16Async(CUdeviceptr dstDevice, unsigned short us, size_t N, CUstream hStream);
    CUresult __stdcall cuMemsetD32Async(CUdeviceptr dstDevice, unsigned int ui, size_t N, CUstream hStream);
    CUresult __stdcall cuMemsetD2D8Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned char uc, size_t Width, size_t Height, CUstream hStream);
    CUresult __stdcall cuMemsetD2D16Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned short us, size_t Width, size_t Height, CUstream hStream);
    CUresult __stdcall cuMemsetD2D32Async(CUdeviceptr dstDevice, size_t dstPitch, unsigned int ui, size_t Width, size_t Height, CUstream hStream);
    CUresult __stdcall cuArrayCreate_v2(CUarray *pHandle, const CUDA_ARRAY_DESCRIPTOR *pAllocateArray);
    CUresult __stdcall cuArrayGetDescriptor_v2(CUDA_ARRAY_DESCRIPTOR *pArrayDescriptor, CUarray hArray);
    CUresult __stdcall cuArrayDestroy(CUarray hArray);
    CUresult __stdcall cuArray3DCreate_v2(CUarray *pHandle, const CUDA_ARRAY3D_DESCRIPTOR *pAllocateArray);
    CUresult __stdcall cuArray3DGetDescriptor_v2(CUDA_ARRAY3D_DESCRIPTOR *pArrayDescriptor, CUarray hArray);
    CUresult __stdcall cuMipmappedArrayCreate(CUmipmappedArray *pHandle, const CUDA_ARRAY3D_DESCRIPTOR *pMipmappedArrayDesc, unsigned int numMipmapLevels);
    CUresult __stdcall cuMipmappedArrayGetLevel(CUarray *pLevelArray, CUmipmappedArray hMipmappedArray, unsigned int level);
    CUresult __stdcall cuMipmappedArrayDestroy(CUmipmappedArray hMipmappedArray);
    CUresult __stdcall cuPointerGetAttribute(void *data, CUpointer_attribute attribute, CUdeviceptr ptr);
    CUresult __stdcall cuMemPrefetchAsync(CUdeviceptr devPtr, size_t count, CUdevice dstDevice, CUstream hStream);
    CUresult __stdcall cuMemAdvise(CUdeviceptr devPtr, size_t count, CUmem_advise advice, CUdevice device);
    CUresult __stdcall cuMemRangeGetAttribute(void *data, size_t dataSize, CUmem_range_attribute attribute, CUdeviceptr devPtr, size_t count);
    CUresult __stdcall cuMemRangeGetAttributes(void **data, size_t *dataSizes, CUmem_range_attribute *attributes, size_t numAttributes, CUdeviceptr devPtr, size_t count);
    CUresult __stdcall cuPointerSetAttribute(const void *value, CUpointer_attribute attribute, CUdeviceptr ptr);
    CUresult __stdcall cuPointerGetAttributes(unsigned int numAttributes, CUpointer_attribute *attributes, void **data, CUdeviceptr ptr);
    CUresult __stdcall cuStreamCreate(CUstream *phStream, unsigned int Flags);
    CUresult __stdcall cuStreamCreateWithPriority(CUstream *phStream, unsigned int flags, int priority);
    CUresult __stdcall cuStreamGetPriority(CUstream hStream, int *priority);
    CUresult __stdcall cuStreamGetFlags(CUstream hStream, unsigned int *flags);
    CUresult __stdcall cuStreamGetCtx(CUstream hStream, CUcontext *pctx);
    CUresult __stdcall cuStreamWaitEvent(CUstream hStream, CUevent hEvent, unsigned int Flags);
    CUresult __stdcall cuStreamAddCallback(CUstream hStream, CUstreamCallback callback, void *userData, unsigned int flags);
    CUresult __stdcall cuStreamBeginCapture(CUstream hStream);
    CUresult __stdcall cuStreamEndCapture(CUstream hStream, CUgraph *phGraph);
    CUresult __stdcall cuStreamIsCapturing(CUstream hStream, CUstreamCaptureStatus *captureStatus);
    CUresult __stdcall cuStreamAttachMemAsync(CUstream hStream, CUdeviceptr dptr, size_t length, unsigned int flags);
    CUresult __stdcall cuStreamQuery(CUstream hStream);
    CUresult __stdcall cuStreamSynchronize(CUstream hStream);
    CUresult __stdcall cuStreamDestroy_v2(CUstream hStream);
    CUresult __stdcall cuEventCreate(CUevent *phEvent, unsigned int Flags);
    CUresult __stdcall cuEventRecord(CUevent hEvent, CUstream hStream);
    CUresult __stdcall cuEventQuery(CUevent hEvent);
    CUresult __stdcall cuEventSynchronize(CUevent hEvent);
    CUresult __stdcall cuEventDestroy_v2(CUevent hEvent);
    CUresult __stdcall cuEventElapsedTime(float *pMilliseconds, CUevent hStart, CUevent hEnd);
    CUresult __stdcall cuImportExternalMemory(CUexternalMemory *extMem_out, const CUDA_EXTERNAL_MEMORY_HANDLE_DESC *memHandleDesc);
    CUresult __stdcall cuExternalMemoryGetMappedBuffer(CUdeviceptr *devPtr, CUexternalMemory extMem, const CUDA_EXTERNAL_MEMORY_BUFFER_DESC *bufferDesc);
    CUresult __stdcall cuExternalMemoryGetMappedMipmappedArray(CUmipmappedArray *mipmap, CUexternalMemory extMem, const CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC *mipmapDesc);
    CUresult __stdcall cuDestroyExternalMemory(CUexternalMemory extMem);
    CUresult __stdcall cuImportExternalSemaphore(CUexternalSemaphore *extSem_out, const CUDA_EXTERNAL_SEMAPHORE_HANDLE_DESC *semHandleDesc);
    CUresult __stdcall cuSignalExternalSemaphoresAsync(const CUexternalSemaphore *extSemArray, const CUDA_EXTERNAL_SEMAPHORE_SIGNAL_PARAMS *paramsArray, unsigned int numExtSems, CUstream stream);
    CUresult __stdcall cuWaitExternalSemaphoresAsync(const CUexternalSemaphore *extSemArray, const CUDA_EXTERNAL_SEMAPHORE_WAIT_PARAMS *paramsArray, unsigned int numExtSems, CUstream stream);
    CUresult __stdcall cuDestroyExternalSemaphore(CUexternalSemaphore extSem);
    CUresult __stdcall cuStreamWaitValue32(CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags);
    CUresult __stdcall cuStreamWaitValue64(CUstream stream, CUdeviceptr addr, cuuint64_t value, unsigned int flags);
    CUresult __stdcall cuStreamWriteValue32(CUstream stream, CUdeviceptr addr, cuuint32_t value, unsigned int flags);
    CUresult __stdcall cuStreamWriteValue64(CUstream stream, CUdeviceptr addr, cuuint64_t value, unsigned int flags);
    CUresult __stdcall cuStreamBatchMemOp(CUstream stream, unsigned int count, CUstreamBatchMemOpParams *paramArray, unsigned int flags);
    CUresult __stdcall cuFuncGetAttribute(int *pi, CUfunction_attribute attrib, CUfunction hfunc);
    CUresult __stdcall cuFuncSetAttribute(CUfunction hfunc, CUfunction_attribute attrib, int value);
    CUresult __stdcall cuFuncSetCacheConfig(CUfunction hfunc, CUfunc_cache config);
    CUresult __stdcall cuFuncSetSharedMemConfig(CUfunction hfunc, CUsharedconfig config);
    CUresult __stdcall cuLaunchKernel(CUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, CUstream hStream, void **kernelParams, void **extra);
    CUresult __stdcall cuLaunchCooperativeKernel(CUfunction f, unsigned int gridDimX, unsigned int gridDimY, unsigned int gridDimZ, unsigned int blockDimX, unsigned int blockDimY, unsigned int blockDimZ, unsigned int sharedMemBytes, CUstream hStream, void **kernelParams);
    CUresult __stdcall cuLaunchCooperativeKernelMultiDevice(CUDA_LAUNCH_PARAMS *launchParamsList, unsigned int numDevices, unsigned int flags);
    CUresult __stdcall cuLaunchHostFunc(CUstream hStream, CUhostFn fn, void *userData);
    __declspec(deprecated) CUresult __stdcall cuFuncSetBlockShape(CUfunction hfunc, int x, int y, int z);
    __declspec(deprecated) CUresult __stdcall cuFuncSetSharedSize(CUfunction hfunc, unsigned int bytes);
    __declspec(deprecated) CUresult __stdcall cuParamSetSize(CUfunction hfunc, unsigned int numbytes);
    __declspec(deprecated) CUresult __stdcall cuParamSeti(CUfunction hfunc, int offset, unsigned int value);
    __declspec(deprecated) CUresult __stdcall cuParamSetf(CUfunction hfunc, int offset, float value);
    __declspec(deprecated) CUresult __stdcall cuParamSetv(CUfunction hfunc, int offset, void *ptr, unsigned int numbytes);
    __declspec(deprecated) CUresult __stdcall cuLaunch(CUfunction f);
    __declspec(deprecated) CUresult __stdcall cuLaunchGrid(CUfunction f, int grid_width, int grid_height);
    __declspec(deprecated) CUresult __stdcall cuLaunchGridAsync(CUfunction f, int grid_width, int grid_height, CUstream hStream);
    __declspec(deprecated) CUresult __stdcall cuParamSetTexRef(CUfunction hfunc, int texunit, CUtexref hTexRef);
    CUresult __stdcall cuGraphCreate(CUgraph *phGraph, unsigned int flags);
    CUresult __stdcall cuGraphAddKernelNode(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies, const CUDA_KERNEL_NODE_PARAMS *nodeParams);
    CUresult __stdcall cuGraphKernelNodeGetParams(CUgraphNode hNode, CUDA_KERNEL_NODE_PARAMS *nodeParams);
    CUresult __stdcall cuGraphKernelNodeSetParams(CUgraphNode hNode, const CUDA_KERNEL_NODE_PARAMS *nodeParams);
    CUresult __stdcall cuGraphAddMemcpyNode(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies, const CUDA_MEMCPY3D *copyParams, CUcontext ctx);
    CUresult __stdcall cuGraphMemcpyNodeGetParams(CUgraphNode hNode, CUDA_MEMCPY3D *nodeParams);
    CUresult __stdcall cuGraphMemcpyNodeSetParams(CUgraphNode hNode, const CUDA_MEMCPY3D *nodeParams);
    CUresult __stdcall cuGraphAddMemsetNode(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies, const CUDA_MEMSET_NODE_PARAMS *memsetParams, CUcontext ctx);
    CUresult __stdcall cuGraphMemsetNodeGetParams(CUgraphNode hNode, CUDA_MEMSET_NODE_PARAMS *nodeParams);
    CUresult __stdcall cuGraphMemsetNodeSetParams(CUgraphNode hNode, const CUDA_MEMSET_NODE_PARAMS *nodeParams);
    CUresult __stdcall cuGraphAddHostNode(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies, const CUDA_HOST_NODE_PARAMS *nodeParams);
    CUresult __stdcall cuGraphHostNodeGetParams(CUgraphNode hNode, CUDA_HOST_NODE_PARAMS *nodeParams);
    CUresult __stdcall cuGraphHostNodeSetParams(CUgraphNode hNode, const CUDA_HOST_NODE_PARAMS *nodeParams);
    CUresult __stdcall cuGraphAddChildGraphNode(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies, CUgraph childGraph);
    CUresult __stdcall cuGraphChildGraphNodeGetGraph(CUgraphNode hNode, CUgraph *phGraph);
    CUresult __stdcall cuGraphAddEmptyNode(CUgraphNode *phGraphNode, CUgraph hGraph, CUgraphNode *dependencies, size_t numDependencies);
    CUresult __stdcall cuGraphClone(CUgraph *phGraphClone, CUgraph originalGraph);
    CUresult __stdcall cuGraphNodeFindInClone(CUgraphNode *phNode, CUgraphNode hOriginalNode, CUgraph hClonedGraph);
    CUresult __stdcall cuGraphNodeGetType(CUgraphNode hNode, CUgraphNodeType *type);
    CUresult __stdcall cuGraphGetNodes(CUgraph hGraph, CUgraphNode *nodes, size_t *numNodes);
    CUresult __stdcall cuGraphGetRootNodes(CUgraph hGraph, CUgraphNode *rootNodes, size_t *numRootNodes);
    CUresult __stdcall cuGraphGetEdges(CUgraph hGraph, CUgraphNode *from, CUgraphNode *to, size_t *numEdges);
    CUresult __stdcall cuGraphNodeGetDependencies(CUgraphNode hNode, CUgraphNode *dependencies, size_t *numDependencies);
    CUresult __stdcall cuGraphNodeGetDependentNodes(CUgraphNode hNode, CUgraphNode *dependentNodes, size_t *numDependentNodes);
    CUresult __stdcall cuGraphAddDependencies(CUgraph hGraph, CUgraphNode *from, CUgraphNode *to, size_t numDependencies);
    CUresult __stdcall cuGraphRemoveDependencies(CUgraph hGraph, CUgraphNode *from, CUgraphNode *to, size_t numDependencies);
    CUresult __stdcall cuGraphDestroyNode(CUgraphNode hNode);
    CUresult __stdcall cuGraphInstantiate(CUgraphExec *phGraphExec, CUgraph hGraph, CUgraphNode *phErrorNode, char *logBuffer, size_t bufferSize);
    CUresult __stdcall cuGraphLaunch(CUgraphExec hGraphExec, CUstream hStream);
    CUresult __stdcall cuGraphExecDestroy(CUgraphExec hGraphExec);
    CUresult __stdcall cuGraphDestroy(CUgraph hGraph);
    CUresult __stdcall cuOccupancyMaxActiveBlocksPerMultiprocessor(int *numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize);
    CUresult __stdcall cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(int *numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize, unsigned int flags);
    CUresult __stdcall cuOccupancyMaxPotentialBlockSize(int *minGridSize, int *blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit);
    CUresult __stdcall cuOccupancyMaxPotentialBlockSizeWithFlags(int *minGridSize, int *blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit, unsigned int flags);
    CUresult __stdcall cuTexRefSetArray(CUtexref hTexRef, CUarray hArray, unsigned int Flags);
    CUresult __stdcall cuTexRefSetMipmappedArray(CUtexref hTexRef, CUmipmappedArray hMipmappedArray, unsigned int Flags);
    CUresult __stdcall cuTexRefSetAddress_v2(size_t *ByteOffset, CUtexref hTexRef, CUdeviceptr dptr, size_t bytes);
    CUresult __stdcall cuTexRefSetAddress2D_v3(CUtexref hTexRef, const CUDA_ARRAY_DESCRIPTOR *desc, CUdeviceptr dptr, size_t Pitch);
    CUresult __stdcall cuTexRefSetFormat(CUtexref hTexRef, CUarray_format fmt, int NumPackedComponents);
    CUresult __stdcall cuTexRefSetAddressMode(CUtexref hTexRef, int dim, CUaddress_mode am);
    CUresult __stdcall cuTexRefSetFilterMode(CUtexref hTexRef, CUfilter_mode fm);
    CUresult __stdcall cuTexRefSetMipmapFilterMode(CUtexref hTexRef, CUfilter_mode fm);
    CUresult __stdcall cuTexRefSetMipmapLevelBias(CUtexref hTexRef, float bias);
    CUresult __stdcall cuTexRefSetMipmapLevelClamp(CUtexref hTexRef, float minMipmapLevelClamp, float maxMipmapLevelClamp);
    CUresult __stdcall cuTexRefSetMaxAnisotropy(CUtexref hTexRef, unsigned int maxAniso);
    CUresult __stdcall cuTexRefSetBorderColor(CUtexref hTexRef, float *pBorderColor);
    CUresult __stdcall cuTexRefSetFlags(CUtexref hTexRef, unsigned int Flags);
    CUresult __stdcall cuTexRefGetAddress_v2(CUdeviceptr *pdptr, CUtexref hTexRef);
    CUresult __stdcall cuTexRefGetArray(CUarray *phArray, CUtexref hTexRef);
    CUresult __stdcall cuTexRefGetMipmappedArray(CUmipmappedArray *phMipmappedArray, CUtexref hTexRef);
    CUresult __stdcall cuTexRefGetAddressMode(CUaddress_mode *pam, CUtexref hTexRef, int dim);
    CUresult __stdcall cuTexRefGetFilterMode(CUfilter_mode *pfm, CUtexref hTexRef);
    CUresult __stdcall cuTexRefGetFormat(CUarray_format *pFormat, int *pNumChannels, CUtexref hTexRef);
    CUresult __stdcall cuTexRefGetMipmapFilterMode(CUfilter_mode *pfm, CUtexref hTexRef);
    CUresult __stdcall cuTexRefGetMipmapLevelBias(float *pbias, CUtexref hTexRef);
    CUresult __stdcall cuTexRefGetMipmapLevelClamp(float *pminMipmapLevelClamp, float *pmaxMipmapLevelClamp, CUtexref hTexRef);
    CUresult __stdcall cuTexRefGetMaxAnisotropy(int *pmaxAniso, CUtexref hTexRef);
    CUresult __stdcall cuTexRefGetBorderColor(float *pBorderColor, CUtexref hTexRef);
    CUresult __stdcall cuTexRefGetFlags(unsigned int *pFlags, CUtexref hTexRef);
    __declspec(deprecated) CUresult __stdcall cuTexRefCreate(CUtexref *pTexRef);
    __declspec(deprecated) CUresult __stdcall cuTexRefDestroy(CUtexref hTexRef);
    CUresult __stdcall cuSurfRefSetArray(CUsurfref hSurfRef, CUarray hArray, unsigned int Flags);
    CUresult __stdcall cuSurfRefGetArray(CUarray *phArray, CUsurfref hSurfRef);
    CUresult __stdcall cuTexObjectCreate(CUtexObject *pTexObject, const CUDA_RESOURCE_DESC *pResDesc, const CUDA_TEXTURE_DESC *pTexDesc, const CUDA_RESOURCE_VIEW_DESC *pResViewDesc);
    CUresult __stdcall cuTexObjectDestroy(CUtexObject texObject);
    CUresult __stdcall cuTexObjectGetResourceDesc(CUDA_RESOURCE_DESC *pResDesc, CUtexObject texObject);
    CUresult __stdcall cuTexObjectGetTextureDesc(CUDA_TEXTURE_DESC *pTexDesc, CUtexObject texObject);
    CUresult __stdcall cuTexObjectGetResourceViewDesc(CUDA_RESOURCE_VIEW_DESC *pResViewDesc, CUtexObject texObject);
    CUresult __stdcall cuSurfObjectCreate(CUsurfObject *pSurfObject, const CUDA_RESOURCE_DESC *pResDesc);
    CUresult __stdcall cuSurfObjectDestroy(CUsurfObject surfObject);
    CUresult __stdcall cuSurfObjectGetResourceDesc(CUDA_RESOURCE_DESC *pResDesc, CUsurfObject surfObject);
    CUresult __stdcall cuDeviceCanAccessPeer(int *canAccessPeer, CUdevice dev, CUdevice peerDev);
    CUresult __stdcall cuCtxEnablePeerAccess(CUcontext peerContext, unsigned int Flags);
    CUresult __stdcall cuCtxDisablePeerAccess(CUcontext peerContext);
    CUresult __stdcall cuDeviceGetP2PAttribute(int *value, CUdevice_P2PAttribute attrib, CUdevice srcDevice, CUdevice dstDevice);
    CUresult __stdcall cuGraphicsUnregisterResource(CUgraphicsResource resource);
    CUresult __stdcall cuGraphicsSubResourceGetMappedArray(CUarray *pArray, CUgraphicsResource resource, unsigned int arrayIndex, unsigned int mipLevel);
    CUresult __stdcall cuGraphicsResourceGetMappedMipmappedArray(CUmipmappedArray *pMipmappedArray, CUgraphicsResource resource);
    CUresult __stdcall cuGraphicsResourceGetMappedPointer_v2(CUdeviceptr *pDevPtr, size_t *pSize, CUgraphicsResource resource);
    CUresult __stdcall cuGraphicsResourceSetMapFlags_v2(CUgraphicsResource resource, unsigned int flags);
    CUresult __stdcall cuGraphicsMapResources(unsigned int count, CUgraphicsResource *resources, CUstream hStream);
    CUresult __stdcall cuGraphicsUnmapResources(unsigned int count, CUgraphicsResource *resources, CUstream hStream);
    CUresult __stdcall cuGetExportTable(const void **ppExportTable, const CUuuid *pExportTableId);
}
