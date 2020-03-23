#include <gtest.h>
#include "List.h"

TEST(TMonom, can_create_monom)
{
	ASSERT_NO_THROW(TMonom mon);
}

TEST(TMonom, assignment_operators_work_correctly)
{
	TMonom m1, m2;
	EXPECT_EQ(m1, m2);
	m1.coeff = 5;
	m1.px = 1;
	m1.py = 2;
	m1.pz = 3;

	m2.coeff = 225;
	m2.px = 1;
	m2.py = 2;
	m2.pz = 3;
	EXPECT_EQ(m1, m2);
	m2.px = 2;
	EXPECT_NE(m1, m2);
}

TEST(TMonom, comparison_operators_work_correctly)
{
	TMonom m1, m2;
	m1.coeff = 5;
	m1.px = 5;
	m1.py = 2;
	m1.pz = 3;

	m2.coeff = 225;
	m2.px = 3;
	m2.py = 2;
	m2.pz = 3;
	EXPECT_GT(m1, m2);
	EXPECT_LT(m2, m1);
}

/*.................................................*/

TEST(TPolynom, can_create_Polynomial)
{
	ASSERT_NO_THROW(TPolynom P);
}

TEST(TPolynom, can_create_polynomial_through_array)
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
	TMonom mon1, mon2;
	mon1.coeff = 6.9;
	mon1.px = 5;
	mon1.py = 5;
	mon1.pz = 3;

	mon2.coeff = 35;
	mon2.px = 1;
	mon2.py = 3;
	mon2.pz = 4;

	TPolynom P;
	P += mon1;
	P += mon2;
	TPolynom Q;
	Q += mon2;
	Q += mon1;
	ASSERT_NO_THROW(P == Q);
	EXPECT_EQ(P, Q);
	Q += mon1;
	EXPECT_NE(P,Q);
}

TEST(TPolynom, can_copy_polynomials)
{
	TMonom mon;
	mon.coeff = 6.9;
	mon.px = 5;
	mon.py = 0;
	mon.pz = 1;
	TPolynom P;
	P += mon;
	ASSERT_NO_THROW(TPolynom Q(P));
	TPolynom Q(P);
	EXPECT_EQ(P, Q);
}

TEST(TPolynom, assignment_operator_works_correctly)
{
	TPolynom P, Q;
	TMonom mon;
	mon.coeff = 6.9;
	mon.px = 5;
	mon.py = 0;
	mon.pz = 1;
	Q += mon;
	EXPECT_NE(P, Q);
	P = Q;
	EXPECT_EQ(P, Q);
}

TEST(TPolynom, can_correctly_add_monom_to_polynom_1)
{
	TMonom mon;
	mon.coeff = 10;
	mon.px = 1;
	mon.py = 2;
	mon.pz = 3;
	int arr1[1][2] = { {110, 123} };
	int arr2[1][2] = { {100, 123} };
	TPolynom pol(arr1, 1);
	TPolynom p(arr2, 1);
	ASSERT_NO_THROW(p += mon);
	EXPECT_EQ(pol, p);
}

TEST(TPolynom, can_correctly_add_monom_to_polynom_2)
{
	TMonom mon;
	mon.coeff = 10;
	mon.px = 2;
	mon.py = 2;
	mon.pz = 3;
	int arr1[2][2] = { {10, 223} , {100, 123} };
	int arr2[1][2] = { {100, 123} };
	TPolynom pol(arr1, 2);
	TPolynom p(arr2, 1);
	ASSERT_NO_THROW(p += mon);
	EXPECT_EQ(pol, p);
}

TEST(TPolynom, can_correctly_add_polynom_to_polynom)
{
	int arr1[2][2] = { {12, 123} , {14, 111} };
	int arr2[3][2] = { {17, 222} , {25, 123} , {7, 000} };
	int arr3[4][2] = { {17, 222} , {37, 123} , {14, 111} , {7, 000} };
	TPolynom pol1(arr1, 2);
	TPolynom pol2(arr2, 3);
	ASSERT_NO_THROW(pol1+=pol2);
	TPolynom p(arr3,4);
	EXPECT_EQ(pol1, p);
}


TEST(TPolynom, first_coeff_becomes_0_after_addition)
{
	int arr1[2][2] = { {12, 123} , {14, 111} };
	int arr2[3][2] = { {17, 222} , {-12, 123} , {7, 000} };
	int arr3[3][2] = { {17, 222} , {14, 111} , {7, 000} };
	TPolynom pol1(arr1, 2);
	TPolynom pol2(arr2, 3);
	ASSERT_NO_THROW(pol1+=pol2);
	TPolynom p(arr3,3);
	EXPECT_EQ(pol1, p);
}

TEST(TPolynom, middle_coeff_becomes_0_after_addition)
{
	int arr1[3][2] = { {12, 123} , {14, 111} , {3, 012} };
	int arr2[3][2] = { {17, 222} , {-14, 111} , {7, 000} };
	int arr3[4][2] = { {17, 222} , {12, 123} , {3, 012} , {7, 000} };
	TPolynom pol1(arr1, 3);
	TPolynom pol2(arr2, 3);
	ASSERT_NO_THROW(pol1+=pol2);
	TPolynom p(arr3,4);
	EXPECT_EQ(pol1, p);
}

TEST(TPolynom, last_coeff_becomes_0_after_addition)
{
	int arr1[3][2] = { {12, 123} , {14, 111} , {3, 012} };
	int arr2[3][2] = { {17, 222} , {25, 111} , {-3, 012} };
	int arr3[3][2] = { {17, 222} , {12, 123} , {39, 111} };
	TPolynom pol1(arr1, 3);
	TPolynom pol2(arr2, 3);
	ASSERT_NO_THROW(pol1+=pol2);
	TPolynom p(arr3,3);
	EXPECT_EQ(pol1, p);
}

TEST(TPolynom, can_multiply_by_monom)
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