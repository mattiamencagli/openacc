#include <array>
#include <vector>
#include <cstdio>

#define n 3

using item = std::array<int,n>;
struct Foo {
  std::vector<item*> data_;
  item ** ptr_;
  Foo() {
    data_.push_back(new item[1024]);
    ptr_=data_.data();
  }
  #pragma acc routine seq
  void addItem(item &itm, int i) {
    ptr_[i/1024][i%1024] = itm;
  }  
};

int main() {

  Foo f;
  item itm;

#pragma acc parallel loop copy(f, f.data_)
  for (int i=0;i<n;++i){
	printf("i=%d, i/1024=%d, i%1024=%d\n",i, i/1024,i%1024);
    f.ptr_[i/1024][i%1024] = itm;
  }

  printf("Done with expanded\n");
#pragma acc parallel loop copy(f, f.data_)
  for (int i=0;i<n;++i){
	printf("i=%d, i/1024=%d, i%1024=%d\n",i, i/1024,i%1024);
    f.addItem(itm,i);
  }
}
