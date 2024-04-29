#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
/*ѧ����Ϣ�ṹ��*/
typedef struct _tStudent {
	char id[128];	/*ѧ��*/
	char name[128];	/*����*/
	char vaccine[128];	/*�������*/
	char dormitory[128];	/*���Һ�*/
	char tel[128];	/*�绰����*/
	char date[128];	/*��У����*/
	char place[128];	/*14��;����*/
	char temperature[128];
}Student, * pStudent;	/*3��������*/
/*ѧ����Ϣ����*/
typedef struct _tStudentList {
	int len;	/*���鳤��*/ int capacity;	/*��������*/ pStudent data;	/*����Ԫ��*/
}StudentList, * pStudentList;
/*������뻺����*/
void emptyStdin() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}
/*�ȴ����������*/
void waitingPressAnyKey() {
	emptyStdin(); getchar();
}
/*����*/ void clearScreen() {
	system("cls");
}
/*Ϊѧ����Ϣ�������ռ�*/
void allocStudentList(pStudentList list) {
	if (list->capacity == 0) {
		/*�״η�������ռ�*/ list->capacity = 16;
		list->data = (pStudent)malloc(sizeof(Student) * list->capacity);
	}
	else if ((list->len == list->capacity)) {
		/*Ϊ����ռ�����*/
		list->capacity *= 2;
		list->data = (pStudent)realloc(list->data, sizeof(Student) * list->capacity);
	}
}
/*����ѧ����Ϣ����*/
void createStudentList(pStudentList list) {
	/*�������ṹ��*/
	memset(list, 0U, sizeof(StudentList));
	/*Ϊ��������ڴ�*/
	allocStudentList(list);
}
/*����ѧ����Ϣ����*/
void destroyStudentList(pStudentList list) {
	if (list->data) {
		//�ͷ������ڴ�
		free(list->data);
	}
	/*�������ṹ��*/
	memset(list, 0U, sizeof(StudentList));
}
/*��ѧ����Ϣ��ӵ�����*/
void addStudentList(pStudentList list, pStudent student) {
	/*��������ռ�*/
	allocStudentList(list);
	list->data[list->len++] = *student;
}
/*��������ɾ��ѧ����Ϣ*/
void removeStudentList(pStudentList list, int position) {
	/*��֤Ҫɾ����Ԫ���±괦�ںϷ�λ��*/
	if (position >= 0 && position < list->len) {
		int index;
		for (index = position + 1; index < list->len; ++index) {
			/*����������Ԫ��ǰ��*/
			list->data[index - 1] = list->data[index];
		}
		/*�������鳤��*/
		--list->len;
	}
}
/*ͨ��ѧ�Ų�������Ԫ��*/
int findStudentListByID(pStudentList list, char* id, int begin) {
	int index;
	for (index = begin; index < list->len; ++index) {
		if (strcmp(list->data[index].id, id) == 0) {
			return index;
		}
	} return -1;
}
/*ͨ��������������Ԫ��*/
int findStudentListByName(pStudentList list, char* name, int begin) {
	int index;
	for (index = begin; index < list->len; ++index) {
		if (strcmp(list->data[index].name, name) == 0) {
			return index;
		}
	} return -1;
}
/*ͨ�����ҺŲ�������Ԫ��*/
int findStudentListByDormitory(pStudentList list, char* dormitory, int begin) {
	int index;
	for (index = begin; index < list->len; ++index) {
		if (strcmp(list->data[index].dormitory, dormitory) == 0) {
			return index;
		}
	} return -1;
}
/*ͨ��������ֲ�������Ԫ��*/
intfindStudentListByVaccine(pStudentListlist, char* vaccine, intbegin)
{
	int index;
	for (index = begin; index < list->len; ++index) {
		if (strcmp(list->data[index].vaccine, vaccine) == 0) {
			return index;
		}
	} return -1;
}
/*��ѧ����Ϣ�洢���ļ�*/
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
		printf("д�ļ�ʧ�ܣ�\n");
	}
}
/*���ļ��м���ѧ����Ϣ*/
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
		printf("���ļ�ʧ�ܣ�\n");
	}
}
/*��ʾѧ����Ϣ����*/
void showStudentTitle() {
	printf("%-10s", "ѧ��"); printf("%-16s", "����"); printf("%-10s", "�������"); printf("%-16s", "���Һ�"); printf("%-16s", "�绰����"); printf("%-16s", "��У����"); printf("%-16s", "14��;����");
	printf("%-16s", "3��������"); printf("\n");
}
/*��ʾѧ����Ϣ*/
void showStudent(pStudent student) {
	printf("%-10s", student->id); printf("%-16s", student->name); printf("%-10s", student->vaccine); printf("%-16s", student->dormitory); printf("%-16s", student->tel); printf("%-16s", student->date); printf("%-16s", student->place); printf("%-16s", student->temperature); printf("\n");
}
/*��ѧ������*/
void sortStudentListByID(StudentList* list) {
	/*ѡ������*/
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
/*����������*/
void sortStudentListByName(StudentList* list) {
	/*ѡ������*/
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
/*��ʾѧ����Ϣ�б�*/
void showStudentList(pStudentList list) {
	int option = 1; while (1) {
		int index; if (option == 0) break; switch (option) {
		case 1:
			sortStudentListByID(list); break;
		case 2:
			sortStudentListByName(list); break;
		}
		printf("#��ʾѧ����Ϣ#\n");
		showStudentTitle();
		for (index = 0; index < list->len; ++index) {
			pStudent student = &list->data[index];
			showStudent(student);
		}
		printf(" 1 ��ѧ������ 2 ���������� 0 ����\n");
		scanf("%d", &option);
	}
}
/*�����������*/
void inputVaccine(char* vaccine) {
	while (1) {
		int option;
		printf("ѡ��������֣�\n"); printf("--------------\n"); printf(" 1 �ѽ���\n"); printf(" 2 δ����\n");
		printf("--------------\n");
		printf("	��ѡ��");
		scanf("%d", &option); switch (option) {
		case 1:
			strcpy(vaccine, "�ѽ���");
			return;
		case 2: strcpy(vaccine, "δ����");
			return;
		}
	}
}
/*�༭ѧ����Ϣ*/
void editStudent(pStudent student) {
	printf("#¼����Ϣ#\n"); if (strlen(student->id)) {
		printf("ѧ�ţ�%s\n", student->id);
	}
	else {
		printf("ѧ�ţ�"); scanf("%s", student->id);
	} printf("������"); scanf("%s", student->name); printf("������֣�");
	inputVaccine(student->vaccine); printf("���Һţ�");
	scanf("%s", student->dormitory); printf("�绰���룺");
	scanf("%s", student->tel); printf("��У���ڣ�");
	scanf("%s", student->date); printf("14��;���أ�");
	scanf("%s", student->place); printf("3�������£�");
	scanf("%s", student->temperature);
}
/*����ѧ����Ϣ*/
void addStudent(pStudentList list) {
	Student student; clearScreen();
	memset(&student, 0, sizeof(Student));
	printf("#���ѧ����Ϣ#\n");
	editStudent(&student);
	if (findStudentListByID(list, student.id, 0) == -1) {
		addStudentList(list, &student); saveFile(list);
		showStudentTitle();
		showStudent(&student);
		printf("�ɹ��������ѧ����Ϣ��\n");
	}
	else {
		printf("��ѧ���Ѵ��ڣ����ʧ�ܣ�\n");
	}
	waitingPressAnyKey();
}
/*�޸�ѧ����Ϣ*/
void updateStudent(pStudentList list) {
	char id[128] = { 0 }; int position = -1; clearScreen();
	printf("#�޸�ѧ����Ϣ#\n"); printf("����ѧ��ѧ�ţ�");
	scanf("%s", id);
	position = findStudentListByID(list, id, 0);
	if (position != -1) {
		editStudent(&list->data[position]); saveFile(list); showStudentTitle(); showStudent(&list->data[position]); printf("�ɹ��޸�����ѧ����Ϣ��\n");
	}
	else {
		printf("δ�ҵ���ѧ����Ϣ!\n");
	}
	waitingPressAnyKey();
}
/*ɾ��ѧ����Ϣ*/
void removeStudent(pStudentList list) {
	char id[128] = { 0 }; int position = -1; clearScreen();
	printf("#ɾ��ѧ����Ϣ#\n"); printf("����ѧ��ѧ�ţ�");
	scanf("%s", id);
	position = findStudentListByID(list, id, 0);
	if (position != -1) {
		showStudentTitle(); showStudent(&list->data[position]); removeStudentList(list, position); saveFile(list);
		printf("�ɹ�ɾ������ѧ����Ϣ!\n");
	}
	else {
		printf("δ�ҵ���ѧ����Ϣ!\n");
	}
	waitingPressAnyKey();
}
/*��ѧ�Ų�ѯ*/
void searchStudentByID(pStudentList list) {
	char id[128] = { 0 }; int position = -1; clearScreen(); printf("#��ѧ�Ų�ѯ#\n"); printf("����ѧ��ѧ�ţ�");
	scanf("%s", id);
	position = findStudentListByID(list, id, 0);
	if (position != -1) {
		showStudentTitle(); do {
			showStudent(&list->data[position]);
			position = findStudentListByID(list, id, position + 1);
		} while (position != -1);
	}
	else {
		printf("δ�ҵ���ѧ����Ϣ!\n");
	}
	waitingPressAnyKey();
}
/*��������ѯ*/
void searchStudentByName(pStudentList list) {
	char name[128] = { 0 };
	int position = -1; clearScreen(); printf("#��ѧ�Ų�ѯ#\n"); printf("����ѧ��������");
	scanf("%s", name);
	position = findStudentListByName(list, name, 0);
	if (position != -1) {
		showStudentTitle(); do {
			showStudent(&list->data[position]);
			position = findStudentListByName(list, name, position + 1);
		} while (position != -1);
	}
	else {
		printf("δ�ҵ���ѧ����Ϣ!\n");
	}
	waitingPressAnyKey();
}
/*�����ҺŲ�ѯ*/
void searchStudentByDormitory(pStudentList list) {
	char dormitory[128] = { 0 };
	int position = -1;
	clearScreen();
	printf("#�����ҺŲ�ѯ#\n"); printf("�������Һţ�"); scanf("%s", dormitory);
	position = findStudentListByDormitory(list, dormitory, 0);
	if (position != -1) {
		showStudentTitle(); do {
			showStudent(&list->data[position]);
			position = findStudentListByDormitory(list, dormitory, position + 1);
		} while (position != -1);
	}
	else {
		printf("δ�ҵ���ѧ����Ϣ!\n");
	}
	waitingPressAnyKey();
}
/*��������ֲ�ѯ*/
void searchStudentByVaccine(pStudentList list) {
	char vaccine[128] = { 0 };
	int position = -1;
	clearScreen();
	printf("#��������ֲ�ѯ#\n");
	inputVaccine(vaccine);
	position = findStudentListByVaccine(list, vaccine, 0);
	if (position != -1) {
		showStudentTitle(); do {
			showStudent(&list->data[position]);
			position = findStudentListByVaccine(list, vaccine, position + 1);
		} while (position != -1);
	}
	else {
		printf("δ�ҵ���ѧ����Ϣ!\n");
	}
	waitingPressAnyKey();
}
/*��ѯѧ����Ϣ*/
void searchStudent(pStudentList list) {
	while (1) {
		int option;
		clearScreen();
		printf("#��ѯѧ����Ϣ#\n"); printf(" 1 ��ѧ�Ų�ѯ\n"); printf(" 2 ��������ѯ\n"); printf(" 3 �����ҺŲ�ѯ\n"); printf(" 4 ��������ֲ�ѯ\n"); printf(" 0 ����\n"); scanf("%d", &option); if (option == 0) break; switch (option) {
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
/*�Ų�ѧ����Ϣ*/
void filterStudent(pStudentList list) {
	char place[128] = { 0 }; int index; char dormitory_list[1024] = { 0 }; clearScreen(); printf("#�Ų�ѧ����Ϣ#\n"); printf("����������յ�����");
	scanf("%s", place);
	for (index = 0; index < list->len; ++index) {
		pStudent student = &list->data[index]; if (strstr(student->place, place)) {
			strcat(dormitory_list, student->dormitory); strcat(dormitory_list, " ");
		}
	}
	FILE* output = fopen("��ע.txt", "w"); if (output) {
		showStudentTitle();
		for (index = 0; index < list->len; ++index) {
			pStudent student = &list->data[index]; if (strstr(dormitory_list, student->dormitory)) {
				fprintf(output, "%-10s ", student->id); fprintf(output, "%-16s ", student->name); fprintf(output, "%-16s ", student->vaccine); fprintf(output, "%-16s ", student->dormitory); fprintf(output, "%-16s ", student->tel); fprintf(output, "%-16s ", student->date); fprintf(output, "%-16s ", student->place); fprintf(output, "%-16s ", student->temperature); fprintf(output, "\n"); showStudent(student);
			}
		} fclose(output);
		printf("�Ų���Ϣ�Ѿ��ɹ�������\n");
	}
	else {
		printf("д�ļ�ʧ�ܣ�\n");
	}
	waitingPressAnyKey();
}
/*�������*/
void process(pStudentList list) {
	/*���ļ��м���ѧ����Ϣ*/
	loadFile(list);
	/*ѭ���˵�*/ while (1) {
		int option;
		clearScreen();
		printf("#У԰�������ϵͳ#\n"); printf(" 1 ���ѧ����Ϣ\n"); printf(" 2 ���ѧ����Ϣ\n"); printf(" 3 �޸�ѧ����Ϣ\n"); printf(" 4 ɾ��ѧ����Ϣ\n"); printf(" 5 ����ѧ����Ϣ\n"); printf(" 6 �Ų�ѧ����Ϣ\n"); printf(" 0 �˳�ϵͳ\n");
		printf("	��ѡ��");
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
	/*����ѧ����Ϣ����*/
	StudentList list;
	/*����ѧ����Ϣ����*/
	createStudentList(&list);
	/*�������*/
	process(&list);
	/*����ѧ����Ϣ����*/
	destroyStudentList(&list); return 0;
}
