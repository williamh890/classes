dim=[80, 40, 20];

width = dim[0];
depth = dim[1];
height = dim[2];

wall = 2;
drawer_width = dim[0] / 2 - 2.*wall;

s=2;
slop = 2;
drawer_offset = 5;
wall = 2;
drawer_width = dim[0] / 2 - 2.*wall;

scale([1/s, 1/s, 1/s])
    organizer();

module organizer() {

    function add_const(vec, val) =
        [for (v = vec) val + v];

    to_left_drawer = add_const(
        [slop/2, drawer_offset, slop/2],
        wall
    );

    to_right_drawer = add_const(
        [width / 2 + slop / 2, drawer_offset+2*wall, slop / 2],
        wall
    );

    r = [width / 2+2*wall+slop, drawer_offset+wall,0];
    l = [0, drawer_offset+wall, 0];


    rotate([90, 0, 0])
        organizer_body();

    translate(r)
        organizer_drawer(inner_wall=wall, slop=slop);

    translate(l)
        organizer_drawer(inner_wall=wall, slop=slop);
}

module organizer_body() {

difference() {
    cube([width, depth, height]);

    drawer_cutout = [
        drawer_width,
        2+depth - wall,
        height - 2*wall
    ];

    translate([wall, wall, wall])
        cube(drawer_cutout);
    translate([width / 2 + wall, wall, wall])
        cube(drawer_cutout);
}

}

module organizer_drawer(inner_wall, slop) {

difference(){
    cube([drawer_width-slop, depth-wall-slop/10, height-2*wall-slop]);

    translate([inner_wall, inner_wall, inner_wall])
        cube([
            drawer_width-2*inner_wall-slop,
            depth-wall-2*inner_wall-slop/10,
            height-2*wall
        ]);

    translate([(drawer_width-slop) / 2, depth-slop/10, height])
        sphere(d=width/3.5);
}
}




