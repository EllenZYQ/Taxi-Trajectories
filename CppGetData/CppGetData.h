// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 CPPGETDATA_EXPORT
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// CPPGETDATA_API 函数视为自 DLL 导入，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef CPPGETDATA_EXPORTS
#define CPPGETDATA_API __declspec(dllexport)
#else
#define CPPGETDATA_API __declspec(dllimport)
#endif
#define LL long long
const int CarNum = 10358;
const int PointNum = 27161;
using namespace std;

//extern CPPGETDATA_API vector<MetaData> carData[10500];
// 此类导出自 CppGetData.dll

class Mypair{
public:
	int first, second;
};
class Coordinate {
public:
	int longitude, latitude;//所有的坐标点的值都乘以1000
};
class Position{
public:
	int longitude, latitude;
	vector<Mypair> cars;//first代表汽车id，second代表经过的时间
}point[PointNum+5];
class CarInfo{
public:
	vector<int> time,pos;//分别表示经过的时间和点的序列号，时间遵循从小到大
}carInfo[CarNum+5];
map<LL, int> pointMp;//根据点坐标查询点的ID
vector<int> showMap[PointNum];//这里面的数据是交给前端展示用的，以邻接表的方式存储

class CPPGETDATA_API CCppGetData
{
public:
	CCppGetData(void) {
		roaded = 0;
	}
	bool LoadData(const char* address) {//address是加载文件data.txt的绝对目录，此函数完成加载数据以及将数据整理后存入全局变量中
		if (roaded == 1)//防止重复加载，会gg的
			return 0;
		roaded = 1;
		strcpy_s(buffer, address);
		strcat_s(buffer, "\\data.txt");
		ifstream instuf(buffer, ios::in);
		if (!instuf)
		{
			return 0;//文件不存在
		}
		int pn, ind, n, time, tmp;
		LL x;
		instuf >> pn;
		for (int i = 1; i <= pn; i++) {
			instuf >> x;
			pointMp[x] = i;
			point[i].longitude = x / 100000;
			point[i].latitude = x % 100000;
		}
		instuf >> tmp;
		for (int i = 1; i <= 10357; i++) {
			instuf >> x >> n;
			for (int j = 0; j < n; j++) {
				instuf >> time >> ind;
				carInfo[i].time.push_back(time);
				carInfo[i].pos.push_back(ind + 1);
				point[ind + 1].cars.push_back({ time,ind });
			}
		}
		instuf.close();
		return true;
	}
	int timeConversion(int day, int hour, int minu, int sec) {
		return (day - 2) * 86400 + hour * 3600 + minu * 60 + sec;
	}
	//void showTrack(int start, int end) {}
	//void carCount(Coordinate posa, Coordinate posb, int timeStart, int timeEnd) {}
	//vector<Mypair> relevance(Coordinate posa_1, Coordinate posb_1, Coordinate posa_2, Coordinate posb_2, int timeStart, int timeEnd, int interval) {}
	//vector<Mypair> inOut(Coordinate posa, Coordinate posb, int timeStart, int timeEnd, int interval) {}
private:
	int roaded;//标记是否加载过文件，防止重复加载
	char buffer[100];
	CCppGetData * tmp;
};

extern CPPGETDATA_API int nCppGetData;

CPPGETDATA_API int fnCppGetData(void);
