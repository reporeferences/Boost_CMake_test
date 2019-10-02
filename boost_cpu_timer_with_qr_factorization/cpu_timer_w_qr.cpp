#include <boost/timer/timer.hpp>
#include <cmath>
#include <iostream>
#include </home/kavehakbarihamed/Eigen/Dense>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>

using boost::timer::cpu_timer;
using boost::timer::cpu_times;
using boost::timer::nanosecond_type;
using namespace std;
using namespace Eigen;

template<typename _Matrix_Type_>
_Matrix_Type_ pinv_qr(const _Matrix_Type_ &A)
{
	Eigen::FullPivLU< _Matrix_Type_ >lu_decomp(A);

	int rank = lu_decomp.rank();
	if (rank == 0) {
		cout << "WARN::Input Matrix seems to be zero matrix" << endl;
		return A;
	}
	else {
		if (A.rows() > A.cols()) {
			Eigen::ColPivHouseholderQR< _Matrix_Type_ > qr(A);
			qr.compute(A);
			Eigen::MatrixXd R = qr.matrixQR().topLeftCorner(rank, rank).template triangularView<Upper>();
			Eigen::MatrixXd Rpsinv2(A.cols(), A.rows());

			Rpsinv2.setZero();
			Rpsinv2.topLeftCorner(rank, rank) = R.inverse();

			return qr.colsPermutation() * Rpsinv2 * qr.householderQ().inverse();
		}
		else if (A.cols() > A.rows()) {
			Eigen::ColPivHouseholderQR< _Matrix_Type_ > qr(A.transpose());
			qr.compute(A.transpose());
			Eigen::MatrixXd R = qr.matrixQR().topLeftCorner(rank, rank).template triangularView<Upper>();
			Eigen::MatrixXd Rpsinv2(A.rows(), A.cols());

			Rpsinv2.setZero();
			Rpsinv2.topLeftCorner(rank, rank) = R.inverse();
			return (qr.colsPermutation() * Rpsinv2 * qr.householderQ().inverse()).transpose();
		}
		else if (A.cols() == A.rows()) {
			Eigen::CompleteOrthogonalDecomposition< _Matrix_Type_> cod(A);
			return cod.pseudoInverse();
		}
	}
}

int main()
{
nanosecond_type const twenty_seconds(0.001 * 1000000000LL);
nanosecond_type last(0);
cpu_timer timer;
cpu_timer cpu;
cpu_times start_time;
cpu_times current_time;
int cnt=0;

Eigen::MatrixXd A = MatrixXd::Random(18,18);

while (1)
{
  cpu_times const elapsed_times(timer.elapsed());
  //nanosecond_type const elapsed(elapsed_times.system + elapsed_times.user);
  //nanosecond_type const elapsed(elapsed_times.system);
  if (elapsed_times.wall-last >= twenty_seconds)
  {
    cpu.start();
    start_time.wall=cpu.elapsed().wall;
    current_time.wall=start_time.wall;
	  for (int i = 0; i < 1; i++) {
		A.setRandom();
		A.row(1).setZero();
		pinv_qr(A);
    //A*pinv_qr(A);
	  //A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A*A;
    }
    current_time.wall=cpu.elapsed().wall;
    //cout << "check" << cnt%1000 <<endl;
    cout << "time spent:" << (current_time.wall-start_time.wall)*0.000000001 <<endl;
    last = elapsed_times.wall;
    cnt++;
  }
}

return 0;
}
