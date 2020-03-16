#include <gtest.h>
#include "List.h"

TEST(TMonom, can_create_monom)
{
	ASSERT_NO_THROW(TMonom mon);
}

TEST(TMonom, assignment_operators_work_correctly)
{
	TMonom m1, m2;
	EXPECT_EQ(true, m1 == m2);
	EXPECT_EQ(false, m1 != m2);
	m1.coeff = 5;
	m1.px = 1;
	m1.py = 2;
	m1.pz = 3;

	m2.coeff = 225;
	m2.px = 1;
	m2.py = 2;
	m2.pz = 3;
	EXPECT_EQ(true, m1 == m2);
	EXPECT_EQ(false, m1 != m2);
	m2.px = 2;
	EXPECT_EQ(true, m1 < m2);
	EXPECT_EQ(false, m1 > m2);
	EXPECT_EQ(true, m1 != m2);
}

/*.................................................*/

TEST(TPolynom, can_create_Polynomial)
{
	ASSERT_NO_THROW(TPolynom P);
}

TEST(TPolynom, can_create_Polynomial_through_array)
{
	int arr[2][2];
	arr[0][0] = 2;
	arr[1][0] = 1;
	arr[0][1] = 222;
	arr[1][1] = 111;
	ASSERT_NO_THROW(TPolynom p(arr, 2));
}

TEST(TPolynom, equality_operator_works_correctly)
{
	TMonom mon;
	mon.coeff = 5.9;
	mon.px = 11;
	mon.py = 5;
	mon.pz = 0;
	TPolynom P;
	P += mon;
	TPolynom Q;
	Q += mon;
	ASSERT_NO_THROW(P == Q);
	EXPECT_EQ(true, P == Q);
}

TEST(TPolynom, can_copy_Polynomials)
{
	TMonom mon;
	mon.coeff = 6.9;
	mon.px = 11;
	mon.py = 5;
	mon.pz = 0;
	TPolynom P;
	P += mon;
	ASSERT_NO_THROW(TPolynom Q(P));
	TPolynom Q(P);
	EXPECT_EQ(true, P == Q);
}

TEST(TPolynom, assignment_operator_works_correctly)
{
	TPolynom P, Q;
	TMonom mon;
	mon.coeff = 5.9;
	mon.px = 11;
	mon.py = 5;
	mon.pz = 0;
	Q += mon;
	EXPECT_NE(true, P == Q);
	P = Q;
	EXPECT_EQ(true, P == Q);
}

TEST(TPolynom, addition_works_correctly)
{
	TMonom mon;
	mon.coeff = 10;
	mon.px = 1;
	mon.py = 2;
	mon.pz = 3;
	int arr1[1][2];
	int arr[1][2];
	for (int i = 0; i < 1; i++) {
		arr1[i][0] = 110;
		arr1[i][1] = 123;

		arr[i][0] = 100;
		arr[i][1] = 123;
	}
	TPolynom pol(arr1, 1);
	TPolynom p(arr, 1);
	ASSERT_NO_THROW(pol += mon);
	EXPECT_EQ(pol, p);
}

TEST(TPolynom, can_correctly_add_polynom_to_polynom)
{
	int arr1[3][2];
	int arr[2][2];
	for (int i = 0; i < 3; i++) {
		arr1[i][0] = i+1;
		arr1[i][1] = 100*(i+1)+(i+1);
	}
	TPolynom pol(arr1, 3);
	for (int i = 0; i < 3; i++) {
		if(i == 0)
			arr1[i][0] = -(i+1);
		else arr1[i][0] = i+1;
		arr1[i][1] = 100 * (i+1) + i+1;
	}
	TPolynom pol1(arr1, 3);
	for (int i = 0; i < 2; i++) {
		arr[i][0] = i+2;
		arr[i][1] = 100 * (i+2) + i+2;
	}
	cout << pol << pol1;
	ASSERT_NO_THROW(pol+=pol1);
	cout << pol;
	TPolynom p(arr,2);
	EXPECT_EQ(pol, p);
}

TEST(TPolynom, can_multiply_monom)
{
	TMonom mon;
	mon.coeff = 2;
	mon.px = 5;
	mon.py = 0;
	mon.pz = 6;
	int arr1[1][2];
	int arr[1][2];
	for (int i = 0; i < 1; i++) {
		arr1[i][0] = 110;
		arr1[i][1] = 629;
		arr[i][0] = 55;
		arr[i][1] = 123;
	}
	TPolynom pol(arr1, 1);
	TPolynom p(arr, 1);
	ASSERT_NO_THROW(p *= mon);
	EXPECT_EQ(pol, p);
}