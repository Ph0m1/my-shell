需要实现：cd、>、>>、<、|
- cd应该在父进程中实现
- 大部分内容使用exec族函数在子进程中实现
- 