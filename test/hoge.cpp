#include "../vector.hpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <glog/logging.h>

// int main(int ac, char** av) {
//   google::InitGoogleLogging(av[0]);
//   LOG(ERROR) << "main called";

//   std::vector<int> vec = {1, 2, 3, 4};

//   LOG(ERROR) << "before insert";
//   for (size_t i = 0; i < vec.size(); ++i) {
//     LOG(ERROR) << "vec[" << i << "] " << vec[i];
//   }

//   std::vector<int>::iterator itr = vec.insert(vec.begin(), 10, 123);
//   LOG(ERROR) << "*itr " << *itr;

//   LOG(ERROR) << "after insert";
//   for (size_t i = 0; i < vec.size(); ++i) {
//     LOG(ERROR) << "vec[" << i << "] " << vec[i];
//   }
// }

int main(int ac, char** av) {
  google::InitGoogleLogging(av[0]);
  LOG(ERROR) << "start main";

  std::vector<int> libv;
  libv.push_back(1);
  ft::vector<int> ftv;
  ftv.push_back(1);

  std::vector<int>::iterator libret = libv.erase(libv.begin());
  ft::vector<int>::iterator ftret = ftv.erase(ftv.begin());

  for (size_t i = 0; i < libv.size(); ++i) {
    LOG(ERROR) << "libv[" << i << "] " << libv[i];
  }
  for (size_t i = 0; i < ftv.size(); ++i) {
    LOG(ERROR) << " ftv[" << i << "] " << ftv[i];
  }
  LOG(ERROR) << "libv " << *libret;
  LOG(ERROR) << "ftv  " << *ftret;
}
