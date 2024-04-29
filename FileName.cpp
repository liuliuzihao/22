#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
/*学生信息结构体*/
typedef struct _tStudent {
	char id[128];	/*学号*/
	char name[128];	/*姓名*/
	char vaccine[128];	/*疫苗接种*/
	char dormitory[128];	/*寝室号*/
	char tel[128];	/*电话号码*/
	char date[128];	/*返校日期*/
	char place[128];	/*14日途径地*/
	char temperature[128];
}Student, * pStudent;	/*3日内体温*/
/*学生信息数组*/
typedef struct _tStudentList {
	int len;	/*数组长度*/ int capacity;	/*数组容量*/ pStudent data;	/*数组元素*/
}StudentList, * pStudentList;
/*清空输入缓冲区*/
void emptyStdin() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}
/*等待按下任意键*/
void waitingPressAnyKey() {
	emptyStdin(); getchar();
}
/*清屏*/ void clearScreen() {
	system("cls");
}
/*为学生信息数组分配空间*/
void allocStudentList(pStudentList list) {
	if (list->capacity == 0) {
		/*首次分配数组空间*/ list->capacity = 16;
		list->data = (pStudent)malloc(sizeof(Student) * list->capacity);
	}
	else if ((list->len == list->capacity)) {
		/*为数组空间扩容*/
		list->capacity *= 2;
		list->data = (pStudent)realloc(list->data, sizeof(Student) * list->capacity);
	}
}
/*创建学生信息数组*/
void createStudentList(pStudentList list) {
	/*清空数组结构体*/
	memset(list, 0U, sizeof(StudentList));
	/*为数组分配内存*/
	allocStudentList(list);
}
/*销毁学生信息数组*/
void destroyStudentList(pStudentList list) {
	if (list->data) {
		//释放数组内存
		free(list->data);
	}
	/*清空数组结构体*/
	memset(list, 0U, sizeof(StudentList));
}
/*将学生信息添加到数组*/
void addStudentList(pStudentList list, pStudent student) {
	/*分配数组空间*/
	allocStudentList(list);
	list->data[list->len++] = *student;
}
/*从数组中删除学生信息*/
void removeStudentList(pStudentList list, int position) {
	/*保证要删除的元素下标处于合法位置*/
	if (position >= 0 && position < list->len) {
		int index;
		for (index = position + 1; index < list->len; ++index) {
			/*将后续数组元素前移*/
			list->data[index - 1] = list->data[index];
		}
		/*减少数组长度*/
		--list->len;
	}
}
/*通过学号查找数组元素*/
int findStudentListByID(pStudentList list, char* id, int begin) {
	int index;
	for (index = begin; index < list->len; ++index) {
		if (strcmp(list->data[index].id, id) == 0) {
			return index;
		}
	} return -1;
}
/*通过姓名查找数组元素*/
int findStudentListByName(pStudentList list, char* name, int begin) {
	int index;
	for (index = begin; index < list->len; ++index) {
		if (strcmp(list->data[index].name, name) == 0) {
			return index;
		}
	} return -1;
}
/*通过寝室号查找数组元素*/
int findStudentListByDormitory(pStudentList list, char* dormitory, int begin) {
	int index;
	for (index = begin; index < list->len; ++index) {
		if (strcmp(list->data[index].dormitory, dormitory) == 0) {
			return index;
		}
	} return -1;
}
/*通过疫苗接种查找数组元素*/
intfindStudentListByVaccine(pStudentListlist, char* vaccine, intbegin)
{
	int index;
	for (index = begin; index < list->len; ++index) {
		if (strcmp(list->data[index].vaccine, vaccine) == 0) {
			return index;
		}
	} return -1;
}
/*将学生信息存储到文件*/
void saveFile(const pStudentList list) {
	FILE* output = fopen("students.txt", "w");
	if (output) {
		int index;
		for (index = 0; index < list->len; ++index) {
			pStudent student = &list->data[index]; fprintf(output, "%-10s ", student->id); fprintf(output, "%-16s ", student->name); fprintf(output, "%-16s ", student->vaccine); fprintf(output, "%-16s ", student->dormitory); fprintf(output, "%-16s ", student->tel); fprintf(output, "%-16s ", student->date); fprintf(output, "%-16s ", student->place); fprintf(output, "%-16s ", student->temperature); fprintf(output, "\n");
		}
		fclose(output);
	}
	else {
		printf("写文件失败！\n");
	}
}
/*从文件中加载学生信息*/
void loadFile(pStudentList list) {
	FILE* input = fopen("students.txt", "r");
	if (input) {
		Student student = { 0 }; list->len = 0; while (1) {
			if (fscanf(input, "%s", student.id) != 1) break; if (fscanf(input, "%s", student.name) != 1) break; if (fscanf(input, "%s", student.vaccine) != 1) break; if (fscanf(input, "%s", student.dormitory) != 1) break; if (fscanf(input, "%s", student.tel) != 1) break; if (fscanf(input, "%s", student.date) != 1) break; if (fscanf(input, "%s", student.place) != 1) break; if (fscanf(input, "%s", student.temperature) != 1) break;
			addStudentList(list, &student);
		}
		fclose(input);
	}
	else {
		printf("读文件失败！\n");
	}
}
/*显示学生信息标题*/
void showStudentTitle() {
	printf("%-10s", "学号"); printf("%-16s", "姓名"); printf("%-10s", "疫苗接种"); printf("%-16s", "寝室号"); printf("%-16s", "电话号码"); printf("%-16s", "返校日期"); printf("%-16s", "14日途径地");
	printf("%-16s", "3日内体温"); printf("\n");
}
/*显示学生信息*/
void showStudent(pStudent student) {
	printf("%-10s", student->id); printf("%-16s", student->name); printf("%-10s", student->vaccine); printf("%-16s", student->dormitory); printf("%-16s", student->tel); printf("%-16s", student->date); printf("%-16s", student->place); printf("%-16s", student->temperature); printf("\n");
}
/*按学号排序*/
void sortStudentListByID(StudentList* list) {
	/*选择排序*/
	int index, cursor;
	for (index = 0; index < list->len; ++index) {
		int target = index;
		for (cursor = target + 1; cursor < list->len; ++cursor) {
			if (strcmp(list->data[target].id, list->data[cursor].id) > 0)
			{
				target = cursor;
			}
		}
		if (target != index) {
			Student temp = list->data[index]; list->data[index] = list->data[target]; list->data[target] = temp;
		}
	}
}
/*按姓名排序*/
void sortStudentListByName(StudentList* list) {
	/*选择排序*/
	int index, cursor;
	for (index = 0; index < list->len; ++index) {
		int target = index;
		for (cursor = target + 1; cursor < list->len; ++cursor) {
			if (strcmp(list->data[target].name,
				list->data[cursor].name) > 0) {
				target = cursor;
			}
		}
		if (target != index) {
			Student temp = list->data[index]; list->data[index] = list->data[target]; list->data[target] = temp;
		}
	}
}
/*显示学生信息列表*/
void showStudentList(pStudentList list) {
	int option = 1; while (1) {
		int index; if (option == 0) break; switch (option) {
		case 1:
			sortStudentListByID(list); break;
		case 2:
			sortStudentListByName(list); break;
		}
		printf("#显示学生信息#\n");
		showStudentTitle();
		for (index = 0; index < list->len; ++index) {
			pStudent student = &list->data[index];
			showStudent(student);
		}
		printf(" 1 按学号排序 2 按姓名排序 0 返回\n");
		scanf("%d", &option);
	}
}
/*输入疫苗接种*/
void inputVaccine(char* vaccine) {
	while (1) {
		int option;
		printf("选择疫苗接种：\n"); printf("--------------\n"); printf(" 1 已接种\n"); printf(" 2 未接种\n");
		printf("--------------\n");
		printf("	请选择：");
		scanf("%d", &option); switch (option) {
		case 1:
			strcpy(vaccine, "已接种");
			return;
		case 2: strcpy(vaccine, "未接种");
			return;
		}
	}
}
/*编辑学生信息*/
void editStudent(pStudent student) {
	printf("#录入信息#\n"); if (strlen(student->id)) {
		printf("学号：%s\n", student->id);
	}
	else {
		printf("学号："); scanf("%s", student->id);
	} printf("姓名："); scanf("%s", student->name); printf("疫苗接种：");
	inputVaccine(student->vaccine); printf("寝室号：");
	scanf("%s", student->dormitory); printf("电话号码：");
	scanf("%s", student->tel); printf("返校日期：");
	scanf("%s", student->date); printf("14日途径地：");
	scanf("%s", student->place); printf("3日内体温：");
	scanf("%s", student->temperature);
}
/*输入学生信息*/
void addStudent(pStudentList list) {
	Student student; clearScreen();
	memset(&student, 0, sizeof(Student));
	printf("#添加学生信息#\n");
	editStudent(&student);
	if (findStudentListByID(list, student.id, 0) == -1) {
		addStudentList(list, &student); saveFile(list);
		showStudentTitle();
		showStudent(&student);
		printf("成功添加以上学生信息！\n");
	}
	else {
		printf("该学号已存在，添加失败！\n");
	}
	waitingPressAnyKey();
}
/*修改学生信息*/
void updateStudent(pStudentList list) {
	char id[128] = { 0 }; int position = -1; clearScreen();
	printf("#修改学生信息#\n"); printf("输入学生学号：");
	scanf("%s", id);
	position = findStudentListByID(list, id, 0);
	if (position != -1) {
		editStudent(&list->data[position]); saveFile(list); showStudentTitle(); showStudent(&list->data[position]); printf("成功修改以上学生信息！\n");
	}
	else {
		printf("未找到该学生信息!\n");
	}
	waitingPressAnyKey();
}
/*删除学生信息*/
void removeStudent(pStudentList list) {
	char id[128] = { 0 }; int position = -1; clearScreen();
	printf("#删除学生信息#\n"); printf("输入学生学号：");
	scanf("%s", id);
	position = findStudentListByID(list, id, 0);
	if (position != -1) {
		showStudentTitle(); showStudent(&list->data[position]); removeStudentList(list, position); saveFile(list);
		printf("成功删除以上学生信息!\n");
	}
	else {
		printf("未找到该学生信息!\n");
	}
	waitingPressAnyKey();
}
/*按学号查询*/
void searchStudentByID(pStudentList list) {
	char id[128] = { 0 }; int position = -1; clearScreen(); printf("#按学号查询#\n"); printf("输入学生学号：");
	scanf("%s", id);
	position = findStudentListByID(list, id, 0);
	if (position != -1) {
		showStudentTitle(); do {
			showStudent(&list->data[position]);
			position = findStudentListByID(list, id, position + 1);
		} while (position != -1);
	}
	else {
		printf("未找到该学生信息!\n");
	}
	waitingPressAnyKey();
}
/*按姓名查询*/
void searchStudentByName(pStudentList list) {
	char name[128] = { 0 };
	int position = -1; clearScreen(); printf("#按学号查询#\n"); printf("输入学生姓名：");
	scanf("%s", name);
	position = findStudentListByName(list, name, 0);
	if (position != -1) {
		showStudentTitle(); do {
			showStudent(&list->data[position]);
			position = findStudentListByName(list, name, position + 1);
		} while (position != -1);
	}
	else {
		printf("未找到该学生信息!\n");
	}
	waitingPressAnyKey();
}
/*按寝室号查询*/
void searchStudentByDormitory(pStudentList list) {
	char dormitory[128] = { 0 };
	int position = -1;
	clearScreen();
	printf("#按寝室号查询#\n"); printf("输入寝室号："); scanf("%s", dormitory);
	position = findStudentListByDormitory(list, dormitory, 0);
	if (position != -1) {
		showStudentTitle(); do {
			showStudent(&list->data[position]);
			position = findStudentListByDormitory(list, dormitory, position + 1);
		} while (position != -1);
	}
	else {
		printf("未找到该学生信息!\n");
	}
	waitingPressAnyKey();
}
/*按疫苗接种查询*/
void searchStudentByVaccine(pStudentList list) {
	char vaccine[128] = { 0 };
	int position = -1;
	clearScreen();
	printf("#按疫苗接种查询#\n");
	inputVaccine(vaccine);
	position = findStudentListByVaccine(list, vaccine, 0);
	if (position != -1) {
		showStudentTitle(); do {
			showStudent(&list->data[position]);
			position = findStudentListByVaccine(list, vaccine, position + 1);
		} while (position != -1);
	}
	else {
		printf("未找到该学生信息!\n");
	}
	waitingPressAnyKey();
}
/*查询学生信息*/
void searchStudent(pStudentList list) {
	while (1) {
		int option;
		clearScreen();
		printf("#查询学生信息#\n"); printf(" 1 按学号查询\n"); printf(" 2 按姓名查询\n"); printf(" 3 按寝室号查询\n"); printf(" 4 按疫苗接种查询\n"); printf(" 0 返回\n"); scanf("%d", &option); if (option == 0) break; switch (option) {
		case 1:
			searchStudentByID(list); break;
		case 2:
			searchStudentByName(list); break;
		case 3:
			searchStudentByDormitory(list); break;
		case 4:
			searchStudentByVaccine(list); break;
		}
	}
}
/*排查学生信息*/
void filterStudent(pStudentList list) {
	char place[128] = { 0 }; int index; char dormitory_list[1024] = { 0 }; clearScreen(); printf("#排查学生信息#\n"); printf("输入疫情风险地区：");
	scanf("%s", place);
	for (index = 0; index < list->len; ++index) {
		pStudent student = &list->data[index]; if (strstr(student->place, place)) {
			strcat(dormitory_list, student->dormitory); strcat(dormitory_list, " ");
		}
	}
	FILE* output = fopen("关注.txt", "w"); if (output) {
		showStudentTitle();
		for (index = 0; index < list->len; ++index) {
			pStudent student = &list->data[index]; if (strstr(dormitory_list, student->dormitory)) {
				fprintf(output, "%-10s ", student->id); fprintf(output, "%-16s ", student->name); fprintf(output, "%-16s ", student->vaccine); fprintf(output, "%-16s ", student->dormitory); fprintf(output, "%-16s ", student->tel); fprintf(output, "%-16s ", student->date); fprintf(output, "%-16s ", student->place); fprintf(output, "%-16s ", student->temperature); fprintf(output, "\n"); showStudent(student);
			}
		} fclose(output);
		printf("排查信息已经成功导出。\n");
	}
	else {
		printf("写文件失败！\n");
	}
	waitingPressAnyKey();
}
/*进入程序*/
void process(pStudentList list) {
	/*从文件中加载学生信息*/
	loadFile(list);
	/*循环菜单*/ while (1) {
		int option;
		clearScreen();
		printf("#校园疫情防控系统#\n"); printf(" 1 浏览学生信息\n"); printf(" 2 添加学生信息\n"); printf(" 3 修改学生信息\n"); printf(" 4 删除学生信息\n"); printf(" 5 搜索学生信息\n"); printf(" 6 排查学生信息\n"); printf(" 0 退出系统\n");
		printf("	请选择：");
		scanf("%d", &option); if (option == 0) break; switch (option) {
		case 1:
			showStudentList(list); break;
		case 2:
			addStudent(list); break;
		case 3:
			updateStudent(list); break;
		case 4:
			removeStudent(list); break;
		case 5:
			searchStudent(list); break;
		case 6:
			filterStudent(list); break;
		}
	}
}
int main() {
	/*定义学生信息数组*/
	StudentList list;
	/*创建学生信息数组*/
	createStudentList(&list);
	/*进入程序*/
	process(&list);
	/*销毁学生信息数组*/
	destroyStudentList(&list); return 0;
}
