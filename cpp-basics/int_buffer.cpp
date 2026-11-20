#include <iostream>
#include <cstddef>
#include <climits>
#include <cstdint>
#include <string>

class IntBuffer {
public:
    explicit IntBuffer(std::size_t sz) : n(sz), ptr(new int[sz]()) {}
    ~IntBuffer() { delete[] ptr; }

    IntBuffer(const IntBuffer &) = delete;
    IntBuffer &operator=(const IntBuffer &) = delete;

    std::size_t size() const;                    // returns n
    int set(std::size_t i, int v);               // 0, or -1 if i >= n (nothing written)
    int get(std::size_t i, int &out) const;      // 0, or -1 if i >= n (out unchanged)

private:
    std::size_t n;
    int *ptr;
};

std::size_t IntBuffer::size() const{
    return n;
}

int IntBuffer::set(std::size_t i, int v){
    if(i >= n){return -1;}
    ptr[i] = v;
    return 0;
}

int IntBuffer::get(std::size_t i, int &out) const{
    if(i >= n){return -1;}
    out = ptr[i];
    return 0;
}

int check(const char *label, int got, int expected){
    if(got != expected){
        std::cout << label << " : FAIL; got " << got << " expected " << expected << std::endl;
        return 1;
    }
    std::cout << label << " : PASS" << std::endl; 
    return 0;
}

int main()
{
    int fail = 0;
    
    // Test Case-1
    {
        IntBuffer b(3);
        int out;
        int get_res = 0;

        for(std::size_t i = 0; i < b.size(); i++){
            out = 99;
            std::string idx = std::to_string(i);
            
            get_res = b.get(i, out);
            fail += check(("New buffer is zero-filled - get(" + idx + ")").c_str(), get_res, 0);
            fail += check(("New buffer is zero-filled - out after get(" + idx + ")").c_str(), out, 0);

        }
    }

    // Test Case-2
    {
        IntBuffer b(0);
        int out = 99;
        std::size_t i = 0;

        int get_res = b.get(i, out);
        fail += check("Size-0 buffer: get rejected", get_res, -1);
        fail += check("Size-0 buffer: out value unchanged", out, 99);

    }

    // Test Case-3
    {
        IntBuffer b(4);
        int set_val = 5;
        std::size_t i = 1;

        int set_res = b.set(i, set_val);
        fail += check("Set, then read back - set value", set_res, 0);

        int out;
        int get_res = 0;
        int expected[4] = {0,set_val,0,0};
        for(std::size_t j = 0; j < (sizeof(expected)/sizeof(expected[0])); j++){
            out = 99;
            std::string idx = std::to_string(j);
            
            get_res = b.get(j, out);
            fail += check(("Set, then read back - get(" + idx + ")").c_str(), get_res, 0);
            fail += check(("Set, then read back - out after get(" + idx + ")").c_str(), out, expected[j]);

        }
    }

    // Test Case-4
    {
        IntBuffer b(0);
        int set_val = 5;
        std::size_t i = 0;

        int set_res = b.set(i, set_val);
        fail += check("Size-0 buffer - set rejected", set_res, -1);
    }

    // Test Case-5
    {
        IntBuffer a(0), b(1), c(3);

        std::size_t a_size = a.size();
        fail += check("size() reports constructed size - IntBuffer(0)", static_cast<int>(a_size), 0);
        
        std::size_t b_size = b.size();
        fail += check("size() reports constructed size - IntBuffer(1)", static_cast<int>(b_size), 1);

        std::size_t c_size = c.size();
        fail += check("size() reports constructed size - IntBuffer(3)", static_cast<int>(c_size), 3);
    }

    // Test Case-6
    {
        IntBuffer b(4);
        int set_val = 7;
        std::size_t i = 3;

        int set_res = b.set(i, set_val);
        fail += check("Last valid index works - set idx 3 to 7", set_res, 0);

        int out = 99;
        int get_res = b.get(i, out);
        fail += check("Last valid index works - get idx 3", get_res, 0);
        fail += check("Last valid index works - write to out", out, set_val);
    }

    // Test Case-7
    {
        IntBuffer b(4);
        int set_val = 7;
        std::size_t i = 4;

        int set_res = b.set(i, set_val);
        fail += check("set at i==n rejected", set_res, -1);

        int out;
        int get_res = 0;
        for(std::size_t j = 0; j < b.size(); j++){
            out = 99;
            std::string idx = std::to_string(j);

            get_res = b.get(j, out);
            fail += check(("set at i==n rejected - get(" + idx + ")").c_str(), get_res, 0);
            fail += check(("set at i==n rejected - out after get(" + idx + ")").c_str(), out, 0);
        }
    }

    // Test Case-8
    {
        IntBuffer b(4);
        int out = 99;
        std::size_t i = 4;

        int get_res = b.get(i, out);
        fail += check("get at i==n rejected", get_res, -1);
        fail += check("get at i==n rejected - out unchanged", out, 99);
    }

    // Test Case-9
    {
        IntBuffer b(4);
        std::size_t idx = SIZE_MAX;
        int set_val = 7;

        int set_res = b.set(idx, set_val);
        fail += check("Very large index rejected - set", set_res, -1);

        int out = 99;
        int get_res = b.get(idx, out);
        fail += check("Very large index rejected - get", get_res, -1);
        fail += check("Very large index rejected - out unchanged", out, 99);
    }

    // Test Case-10
    {
        IntBuffer b(1);
        std::size_t idx = 0;
        int first_val = 5;

        int set_res = b.set(idx, first_val);
        fail += check("Size-1 buffer - set idx = 0", set_res, 0);

        int out = 99;
        int get_res = b.get(idx, out);
        fail += check("Size-1 buffer - get idx = 0", get_res, 0);
        fail += check("Size-1 buffer - out val updated", out, first_val);

        idx = 1;
        int rejected_val = 9;
        set_res = b.set(idx, rejected_val);
        fail += check("Size-1 buffer - set idx = 1", set_res, -1);

        idx = 0;
        out = 99;
        get_res = b.get(idx, out);
        fail += check("Size-1 buffer - get idx = 0 after failed set", get_res, 0);
        fail += check("Size-1 buffer - out val after failed set", out, first_val);
    }

    // Test Case-11
    {
        IntBuffer b(2);
        int first_val = 5;
        int second_val = 8;

        int set_res = b.set(0, first_val);
        fail += check("Overwrite - first set(0) return", set_res, 0);
        set_res = b.set(0, second_val);
        fail += check("Overwrite - second set(0) return", set_res, 0);

        int expected[2] = {second_val, 0};
        int out;
        int get_res = 0;
        for(std::size_t j = 0; j < (sizeof(expected)/sizeof(expected[0])); j++){
            out = 99;
            std::string idx = std::to_string(j);

            get_res = b.get(j, out);
            fail += check(("Overwrite - get(" + idx + ") return").c_str(), get_res, 0);
            fail += check(("Overwrite - out after get(" + idx + ")").c_str(), out, expected[j]);
        }
    }

    // Test Case-12
    {
        IntBuffer b(3);
        int expected[3] = {-1, INT_MIN, INT_MAX};
        const std::size_t count = sizeof(expected)/sizeof(expected[0]);

        for(std::size_t j = 0; j < count; j++){
            std::string idx = std::to_string(j);
            int set_res = b.set(j, expected[j]);
            fail += check(("Negative/extreme values - set(" + idx + ") return").c_str(), set_res, 0);
        }

        int out;
        int get_res = 0;
        for(std::size_t j = 0; j < count; j++){
            out = 99;
            std::string idx = std::to_string(j);

            get_res = b.get(j, out);
            fail += check(("Negative/extreme values - get(" + idx + ") return").c_str(), get_res, 0);
            fail += check(("Negative/extreme values - out after get(" + idx + ")").c_str(), out, expected[j]);
        }
    }

    // Test Case-13
    {
        IntBuffer a(3), b(3);
        int set_val = 5;

        int set_res = a.set(0, set_val);
        fail += check("Independent buffers - a.set(0) return", set_res, 0);

        int out = 99;
        int get_res = b.get(0, out);
        fail += check("Independent buffers - b.get(0) return", get_res, 0);
        fail += check("Independent buffers - b unaffected by a.set", out, 0);

        out = 99;
        get_res = a.get(0, out);
        fail += check("Independent buffers - a.get(0) return", get_res, 0);
        fail += check("Independent buffers - a holds its value", out, set_val);
    }

    std::cout << fail << " checks FAILED\n";
    return fail != 0;
}
