# Generate Autonomous(genom) - an FTC Autonomous generator language for team Phoenix RO026-19079

Example:

```
#rate_start SPEED=0.4
    carusel.setPower(SPEED);
    !rate_end
#rate_end time=1000 recorded now
    if(recorded == 0){
        now = t.milliseconds();
        recorded = 1;
    }else{
        if(t.milliseconds() > now + 1000)
        {
            recorded = 0;
            if(CapstonePosition.Position == 1)
                !spline_lift lift_raise_1
            if(CapstonePosition.Position == 2)
                !spline_lift lift_raise_2
            if(CapstonePosition.Position == 3)
                !spline_lift lift_raise_3
        }
    }
    carusel.setPower(0);

#lift_raise_1 level1=350
    lift.setAngle(level1,0.5);
    if(lift.getAngle() == level1)
        !spline_forward
#lift_raise_2 level2=950
    lift.setAngle(level2,0.5);
    if(lift.getAngle() == level2)
        !spline_forward
#lift_raise_3 level3=1350
    lift.setAngle(level3,0.5);
    if(lift.getAngle() == level3)
        !spline_forward

#start
    !spline_duck

#drop time=1000 recorded now
    if(recorded == 0){
        now = t.milliseconds();
        recorded = 1;
    }else{
        if(t.milliseconds() > now + 1000)
        {
            recorded = 0;
            cupa.setPosition(0);
            !spline_back
        }
        cupa.setPosition(0.75);
    }
    


@spline_duck [100,0,180] rate_start
@spline_lift [-300,0,0] spline_forward
@spline_forward [0,200,0,0] drop
@spline_back [0,-200,-90] spline_forward
 
 ```
 
 You can view the output in the `out` file.
