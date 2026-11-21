#include <cstdio>

struct TestCase{
    const char *label;
    int mm;
    int expected_res;
    int expected_count;
};

class Sensor{
    protected:
        int id;
        int count;
        void record(){
            count += 1;
        }
    
    public:
        Sensor(int i) : id(i), count(0){}
        int get_id() const {return id;}
        int get_count() const {return count;}
};

class RangeSensor : public Sensor{
    private:
        int max_mm;
    
    public:
        RangeSensor(int i, int max) : Sensor(i), max_mm(max){}
        int accept(int mm){
            if(mm >= 0 && mm <= max_mm){
                record();
                return 1;
            }
            return 0;
        }
};

int check(const char* label, int got, int expected){
    if(got != expected){
        std::printf("%s : FAIL. got %d, expected %d\n", label, got, expected);
        return 1;
    }
    std::printf("%s : PASS\n", label);
    return 0;
}

int check_adv(const char* label1, const char* label2, int got, int expected){
    if(got != expected){
        std::printf("%s - %s : FAIL. got %d, expected %d\n", label1, label2, got, expected);
        return 1;
    }
    std::printf("%s - %s : PASS\n", label1, label2);
    return 0;
}

int main(){

    RangeSensor rs(5, 1000);
    
    int id_got = rs.get_id();
    int count_got = rs.get_count();
    std::printf("ID: %d and COUNT: %d\n", id_got, count_got);
    
    int fail = 0;
    fail += check("ID check", id_got, 5);
    fail += check("Count check", count_got, 0);

    TestCase tests[] = {
        { "in range",    500, 1, 1 },
        { "at max",     1000, 1, 2 },
        { "above max",  1001, 0, 2 },
        { "negative",     -1, 0, 2 },
        { "zero",          0, 1, 3 },
    };

    std::size_t len_tests = sizeof(tests)/sizeof(tests[0]);
    for(std::size_t i = 0; i < len_tests; i++){
        int accept_res = rs.accept(tests[i].mm);
        count_got = rs.get_count();
        fail += check_adv(tests[i].label, "accept result check for rs", accept_res, tests[i].expected_res);
        fail += check_adv(tests[i].label, "count check for rs", count_got, tests[i].expected_count);
    }

    RangeSensor q(6,10);
    int accept_q = q.accept(5);
    int count_q = q.get_count();
    fail += check("accept result check for q", accept_q, 1);
    fail += check("count check for q after accept", count_q, 1);

    count_got = rs.get_count();
    fail += check("count check for rs", count_got, 3);

    std::printf("%d checks FAILED\n", fail);
    return fail != 0;
}
