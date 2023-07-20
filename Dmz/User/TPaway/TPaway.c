#include <math.h>

#define RADIUS 6371000.0 // ����뾶

double deg2rad(double deg) {
    return deg *  3.14159265358979323846 / 180.0;
}


//double lat1 = 39.9042; // �����е�γ��
//double lon1 = 116.4074; // �����еľ���
//double lat2 = 31.2304; // �Ϻ��е�γ��
//double lon2 = 121.4737; // �Ϻ��еľ���
//double distance = haversine(lat1, lon1, lat2, lon2);

double haversine(double lat1, double lon1, double lat2, double lon2) {
    double dLat = deg2rad(lat2 - lat1);
    double dLon = deg2rad(lon2 - lon1);
    double a = sin(dLat/2) * sin(dLat/2) +
               cos(deg2rad(lat1)) * cos(deg2rad(lat2)) *
               sin(dLon/2) * sin(dLon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double d = RADIUS * c;
    return d;
}

