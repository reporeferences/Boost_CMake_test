#include <boost/timer/timer.hpp>
#include <cmath>

using boost::timer::cpu_timer;
using boost::timer::cpu_times;
using boost::timer::nanosecond_type;

int main()
{
nanosecond_type const twenty_seconds(0.001 * 1000000000LL);
nanosecond_type last(0);
cpu_timer timer; 
int cnt=0;

while (1)
{
  cpu_times const elapsed_times(timer.elapsed());
  nanosecond_type const elapsed(elapsed_times.system + elapsed_times.user);
  //nanosecond_type const elapsed(elapsed_times.system);
  if (elapsed_times.wall-last >= twenty_seconds)
  {
    std::cout << "check" << cnt%1000 <<std::endl;
    last = elapsed_times.wall;
    cnt++;
  }
}

return 0;
}
