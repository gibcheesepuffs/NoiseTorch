// SPDX-License-Identifier: Apache-2.0 OR MIT OR Unlicense

// Code auto-generated by piet-gpu-derive

struct PathCubicRef {
    uint offset;
};

struct PathSegRef {
    uint offset;
};

struct PathCubic {
    vec2 p0;
    vec2 p1;
    vec2 p2;
    vec2 p3;
    uint path_ix;
    uint trans_ix;
    vec2 stroke;
};

#define PathCubic_size 48

PathCubicRef PathCubic_index(PathCubicRef ref, uint index) {
    return PathCubicRef(ref.offset + index * PathCubic_size);
}

#define PathSeg_Nop 0
#define PathSeg_Cubic 1
#define PathSeg_size 52

PathSegRef PathSeg_index(PathSegRef ref, uint index) {
    return PathSegRef(ref.offset + index * PathSeg_size);
}

struct PathSegTag {
   uint tag;
   uint flags;
};

PathCubic PathCubic_read(Alloc a, PathCubicRef ref) {
    uint ix = ref.offset >> 2;
    uint raw0 = read_mem(a, ix + 0);
    uint raw1 = read_mem(a, ix + 1);
    uint raw2 = read_mem(a, ix + 2);
    uint raw3 = read_mem(a, ix + 3);
    uint raw4 = read_mem(a, ix + 4);
    uint raw5 = read_mem(a, ix + 5);
    uint raw6 = read_mem(a, ix + 6);
    uint raw7 = read_mem(a, ix + 7);
    uint raw8 = read_mem(a, ix + 8);
    uint raw9 = read_mem(a, ix + 9);
    uint raw10 = read_mem(a, ix + 10);
    uint raw11 = read_mem(a, ix + 11);
    PathCubic s;
    s.p0 = vec2(uintBitsToFloat(raw0), uintBitsToFloat(raw1));
    s.p1 = vec2(uintBitsToFloat(raw2), uintBitsToFloat(raw3));
    s.p2 = vec2(uintBitsToFloat(raw4), uintBitsToFloat(raw5));
    s.p3 = vec2(uintBitsToFloat(raw6), uintBitsToFloat(raw7));
    s.path_ix = raw8;
    s.trans_ix = raw9;
    s.stroke = vec2(uintBitsToFloat(raw10), uintBitsToFloat(raw11));
    return s;
}

void PathCubic_write(Alloc a, PathCubicRef ref, PathCubic s) {
    uint ix = ref.offset >> 2;
    write_mem(a, ix + 0, floatBitsToUint(s.p0.x));
    write_mem(a, ix + 1, floatBitsToUint(s.p0.y));
    write_mem(a, ix + 2, floatBitsToUint(s.p1.x));
    write_mem(a, ix + 3, floatBitsToUint(s.p1.y));
    write_mem(a, ix + 4, floatBitsToUint(s.p2.x));
    write_mem(a, ix + 5, floatBitsToUint(s.p2.y));
    write_mem(a, ix + 6, floatBitsToUint(s.p3.x));
    write_mem(a, ix + 7, floatBitsToUint(s.p3.y));
    write_mem(a, ix + 8, s.path_ix);
    write_mem(a, ix + 9, s.trans_ix);
    write_mem(a, ix + 10, floatBitsToUint(s.stroke.x));
    write_mem(a, ix + 11, floatBitsToUint(s.stroke.y));
}

PathSegTag PathSeg_tag(Alloc a, PathSegRef ref) {
    uint tag_and_flags = read_mem(a, ref.offset >> 2);
    return PathSegTag(tag_and_flags & 0xffff, tag_and_flags >> 16);
}

PathCubic PathSeg_Cubic_read(Alloc a, PathSegRef ref) {
    return PathCubic_read(a, PathCubicRef(ref.offset + 4));
}

void PathSeg_Nop_write(Alloc a, PathSegRef ref) {
    write_mem(a, ref.offset >> 2, PathSeg_Nop);
}

void PathSeg_Cubic_write(Alloc a, PathSegRef ref, uint flags, PathCubic s) {
    write_mem(a, ref.offset >> 2, (flags << 16) | PathSeg_Cubic);
    PathCubic_write(a, PathCubicRef(ref.offset + 4), s);
}
