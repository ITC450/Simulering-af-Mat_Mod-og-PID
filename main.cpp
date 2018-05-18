#include <iostream>
#include <fstream>

#include <math.h>

#define PI 3.14159265

using namespace std;

int main() {
    cout << "Simulation:" << fixed << cout.precision(5) << std::endl;
    ofstream myfile;
    myfile.open ("drive.txt");

    float start_pos=0;
    float start_ang=0.7854;

    float r_mat;
    float x{start_pos}, y{0}, x_temp{0}, y_temp{0}, angle{start_ang};
    float phi;
    float delta{1};
    delta=delta/30;
    int time{3};
    float speed{29};
    float error{0};

    float r_pid;
    float z{start_pos}, y2{0}, x_temp2{0}, y_temp2{0}, angle2{start_ang};
    float phi2;
    float error2{0};
    float err;
    float inte;
    float last_err;
    float kp = 0.0065;
    //float ki = 0.0003;
    float ki = 0.0;
    float kd = 0.0006;

    cout << "Delta t:            " << delta << std::endl;
    cout << "Radius:             " << r_mat << std::endl;

    int iterations=time/delta;

    cout << "Total iterations:   " << iterations << std::endl;

    cout << "Iteration: "<< 0 << endl;
    //cout << x << " : "<< y << endl;
    myfile << x  << " " << y << " ";

    //cout << x << " : "<< y << endl;
    myfile << z << " " << y2 << "\n";

    for(int i{1};i<=iterations;i++) {
        cout << endl << "Iteration: "<< i << endl;

        error=(x*cos(-angle))-(16.8*sin(-angle));

        r_mat=abs(16.8/(sin(2*atan(abs(error)/16.8))));

        //cout << "Radius: "<< r_mat << endl;

        //r=abs(r);
        //cout << "error: "<< error << endl;

        phi=2*PI*(speed*delta/(2*PI*r_mat));
        //cout << "Phi: "<< phi << endl;

        //cout << "Phi: "<< phi << endl;

        x_temp=(cos(phi)*r_mat)-r_mat;
        y_temp=(sin(phi)*r_mat);
        //cout << x_temp << " : "<< y_temp << endl;

        if(error<0){
            x=x-((-x_temp*(cos(angle)))-(y_temp*(sin(angle))));
            y=y+((-x_temp*(sin(angle)))+(y_temp*(cos(angle))));
            angle=angle+phi;
        }
        else{
            x=x-((x_temp*(cos(angle)))-(y_temp*(sin(angle))));
            y=y+((x_temp*(sin(angle)))+(y_temp*(cos(angle))));
            angle=angle-phi;
        }

        //cout << "Angle: "<< angle << endl;
        //cout << x << " : "<< y << endl;

        myfile << x << " " << y << " ";


        //###########################################
        cout << "---------------------------" << endl;

        err=(z*cos(-angle2))-(16.8*sin(-angle2));
        err=err/0.04309;

        cout << "err: "<< err << endl;

        double Pout = kp * err; // P delen udregnes
        inte +=  err * delta;  // I delen udregnes
        double Iout = ki * inte;
        double derivative = (err - last_err)/delta;
        double Dout = kd * derivative;

        double output = Pout + Iout+ Dout;

        last_err=err;
        //return output;

        error2=abs(output)+1;

        r_pid=abs((-12*(error2+1))/(2*(error2-1)));

        //r=abs(r);
        cout << "Radius: "<< r_pid << endl;
        cout << "error2: "<< error2 << endl;

        phi2=2*PI*(speed*delta/(2*PI*r_pid));
        cout << "Phi2: "<< phi2 << endl;

        //cout << "Phi: "<< phi << endl;

        x_temp2=(cos(phi2)*r_pid)-r_pid;
        y_temp2=(sin(phi2)*r_pid);
        cout << x_temp2 << " : "<< y_temp2 << endl;

        if(err<0){
            z=z-((-x_temp2*(cos(angle2)))-(y_temp2*(sin(angle2))));
            y2=y2+((-x_temp2*(sin(angle2)))+(y_temp2*(cos(angle2))));
            angle2=angle2+phi2;
        }
        else{
            z=z-((x_temp2*(cos(angle2)))-(y_temp2*(sin(angle2))));
            y2=y2+((x_temp2*(sin(angle2)))+(y_temp2*(cos(angle2))));
            angle2=angle2-phi2;
        }

        cout << "Angle2: "<< angle2 << endl;
        cout << z << " "<< y2 << endl;

        myfile << z << " " << y2 << "\n";

    }
    return 0;
}