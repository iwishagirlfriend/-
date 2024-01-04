using namespace std;
template<class T>
class my_priority_queue {
private:
    // 默认的容器空间大小是1000, 坐标是0
    // room : 实际空间大小  cnt : 当前元素坐标
    int room = 1000, cnt = 0;
    T* que = nullptr;
    
    
    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    
    void swap(T& a, T& b) { T t(a); a = b, b = t; } //交换函数
    void copyof(const T* const a, T* b) {
        // 把a的所有数据倒给b, 并且a的空间大小一定要小于b的空间大小
        for (int i = 1; i <= this->cnt; i++)
            b[i] = a[i];
    }

    //扩张函数
    void expand() {
        // 创建一个新的容器, 把原来容器中的数据倒进新的容器
        // 释放原先的空间, 然后将新的容器给原来的容器, 注意不要释放新空间
        // 最后改变当前的容量
        T* NewQue = new  T[this->room * 2];
        copyof(this->que, NewQue);
        delete[] que;
        que = NewQue;
        this->room = this->room * 2;
    }

    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    void up(int pos) { // 向上浮动
        while (pos != 1 && que[pos] > que[pos / 2]) {
            swap(que[pos], que[pos / 2]);
            pos /= 2;
        }//大根堆
    }

    void down(int pos) { // 下降
        while (pos * 2 <= cnt) { //至少一个儿子, 没有儿子就不用下降了嘛
            if (pos * 2 + 1 > cnt) { //只有左儿子
                if (que[pos] < que[pos * 2]) {
                    swap(que[pos], que[pos * 2]);
                    pos *= 2;
                }
                else break; //比两个儿子都大, 此时满足大根堆的性质, 不用继续比较
            }

            else { //两个儿子都有
                // lson : 左儿子           rson : 右儿子              myself : 当前元素
                T& lson = que[pos * 2], & rson = que[pos * 2 + 1], & myself = que[pos];

                if (myself < lson && myself < rson) { //既小于左儿子, 又小于右儿子
                    if (lson > rson)  swap(myself, lson), pos *= 2; //如果左儿子大于右儿子, 就往左边降
                    else swap(myself, rson), pos = pos * 2 + 1;     //也就是说哪个儿子大就往哪边降
                }
                else if (myself < lson) { //只小于左儿子
                    swap(myself, lson), pos *= 2;
                }
                else if (myself < rson) { //只小于右儿子
                    swap(myself, rson), pos = pos * 2 + 1;
                }
                else break; //比两个儿子都大,此时满足大根堆的性质, 不用继续比较
            }
        }
    }

public:

    //构造函数
    explicit my_priority_queue() {
        this->room = 1000, this->cnt = 0;
        this->que = new T[1000];
        if (que == nullptr)   cout << "创建失败" << endl;
        // 简单的构造函数空间是1000
        // cout<<"创建成功"<<endl;
    }

    explicit my_priority_queue(int len) {
        this->room = len * 2, this->cnt = 0;
        this->que = new T[room];
        if (que == nullptr)   cout << "创建失败" << endl;
        // cout<<"创建成功"<<endl;
    }
    // --------------------------------------------------------------------------------------------------------------------------------------------------------

    //复制函数, 被学长带得风情万种的 学姐 比不上被自己带得风情万种的 学妹
    //注意不会改变容器的room大小
    my_priority_queue(const my_priority_queue& oth) {
        this->cnt = oth.cnt;
        while (this->cnt > this->room)    expand();
        for (int i = 1; i <= this->cnt; i++)
            this->que[i] = oth.que[i];
    }

    // --------------------------------------------------------------------------------------------------------------------------------------------------------

    //功能函数
    int size() { return this->cnt; }     //返回此时堆中元素的数量
    bool empty() { return this->cnt > 0; } //判断是否为空
    int capacity() { return this->room; }
    
    T top() {       
        if (this->cnt > 0) return que[1];
        else {
            cout << "当前医院没有病人哦" << endl;
            return T();
        }
    } //返回堆顶元素, 就是问问这个教室里谁最帅

    void push(const T& a) { // 插入元素
        T t(a);
        this->cnt++;
        if (this->cnt > room) expand();
        que[cnt] = t;
        up(cnt);
    } // 就是又迟到的同学现在进入了教师

    T pop() {  // 删除堆顶元素
        if (this->cnt == 0) { cout << "医院已经没有病人了哦" << endl; return T(); }
        node t = que[1];
        swap(que[1], que[this->cnt]);
        this->cnt--;
        down(1);
        return t;
    } // 就是枪毙当前最帅的人

    // --------------------------------------------------------------------------------------------------------------------------------------------------------
    //析构函数, 释放空间
    ~my_priority_queue() {
        if (que != nullptr)  delete[] que;
        que = nullptr;
        /*下一个更乖*/
    }
};
