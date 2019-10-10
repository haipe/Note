#include <iostream>
#include <list>
#include <vector>


typedef std::list<int> list_int;
typedef std::vector<int> vector_int;

template<typename array_type>
void printf_array_int(array_type& ls)
{
    std::for_each(ls.begin(),ls.end(),[](int i){
        std::cout << i << "; ";
    });
    
    std::cout << std::endl;
}

int insert_sort(vector_int& in)
{
    //printf_array_int<vector_int>(in);
    int run_cnt = 0;
    int size = in.size();
    //第一个相当于有序队列的部分，从第二个开始算作无序部分
    for(int i = 1; i < size; i++)
    {
        int tmp = in[i];//保存一份当前位置的数据，用来记录需要插入的数据。
        //从i开始逐个比较合适位置，找到插入点
        int j = i;
        for(;j > 0; j--)
        {
            //std::cout << "[ " << j << " , " << j - 1 << " ] " << in[j] << " " << in[j-1] << std::endl;
            run_cnt ++;
            //如果比前面的小，则插入到前面的
            if(in[j] < in[j-1])
            {
                //std::cout << "swap [ " << j << " , " << j - 1 << " ] " << in[j] << " " << in[j-1] << std::endl;
                //in[i]已经保存，所以只要把前面的后移即可，最后找到位置之后在用保存的tmp覆盖即可
                in[j]=in[j-1];
                in[j-1] = tmp;
                continue;
            }

            //std::cout << "find insert position :"<< j << std::endl;
            break;
        }

        //找到前一个位置小于来当前比较的位置，即插入到这个之后
        in[j] = tmp;
        //printf_array_int<vector_int>(in);
    }

    return run_cnt;
}

int insert_sort_ex(vector_int& in, int space)//增加一个比较间隔参数
{ 
    //printf_array_int<vector_int>(in);
    int run_cnt = 0;
    int size = in.size();
    //第一个相当于有序队列的部分，从第二个开始算作无序部分
    for(int i = space; i < size; i+= space)
    {
        int tmp = in[i];//保存一份当前位置的数据，用来记录需要插入的数据。
        //从i开始逐个比较合适位置，找到插入点
        int j = i;
        for(;j > 0; j-= space)
        {
            //std::cout << "[ " << j << " , " << j - space << " ] " << in[j] << " " << in[j-space] << std::endl;
            run_cnt ++;
            //如果比前面的小，则插入到前面的
            if(in[j] < in[j-space])
            {
                //std::cout << "swap [ " << j << " , " << j - space << " ] " << in[j] << " " << in[j-space] << std::endl;
                //in[i]已经保存，所以只要把前面的后移即可，最后找到位置之后在用保存的tmp覆盖即可
                in[j]=in[j-space];
                in[j-space] = tmp;
                continue;
            }

            //std::cout << "find insert position :"<< j << std::endl;
            break;
        }

        //找到前一个位置小于来当前比较的位置，即插入到这个之后
        in[j] = tmp;
        //printf_array_int<vector_int>(in);
    }

    return run_cnt;
}

int shell_sort(vector_int& in)
{
    int run_cnt = 0;
    int space = in.size() / 2;
    for(int i = space ; i >= 1 ; i = i/2)
    {
        run_cnt += insert_sort_ex(in,i);
    }

    return run_cnt;
}

void merge_list(list_int& left, list_int& right, list_int& out)
{
    auto left_it = left.begin();
    auto right_it = right.begin();

    while(left_it != left.end() && right_it != right.end())
    {
        if(*left_it <= *right_it)
        {
            out.push_back(*left_it);
            left_it++;
        }
        else
        {
            out.push_back(*right_it);
            right_it++;
        }
    }

    if(left_it == left.end() && right_it == right.end())
        return;

    if(left_it == left.end())
        out.insert(out.end(),right_it,right.end());
    else
        out.insert(out.end(), left_it, left.end());
}

int select_sort(list_int& in, list_int& out)
{
    int run_cnt = 0;
    auto item_in = in.begin();
    out.push_front(*item_in);
    
    for(++item_in ; item_in != in.end() ; item_in ++)
    {
        auto item_out = out.begin();
        for( ; item_out != out.end() ; item_out ++)
        {
            run_cnt ++;
            //头插，第一个小于自己的
            //尾插，可以从最后一个开始遍历
            if(*item_in < *item_out)
            {
                break;
            }
        }

        //if(item_out == out.end())
        //    std::cout << "insert: " << *item_in << " on last;" << std::endl;
        //else
        //    std::cout << "insert: " << *item_in << ", front:" << *item_out << std::endl;
            
        out.insert(item_out,*item_in);
    }

    return run_cnt;
}


int main()
{
    std::cout << "select_sort -------------" << std::endl;
    list_int ls = {1,21,4,6,5,31,22};
    list_int out;
    std::cout << "run count:" << select_sort(ls,out);    
    printf_array_int<list_int>(out);


    std::cout << "merge_list -------------" << std::endl;
    list_int r = {7,8,9,10};
    ls.clear();
    merge_list(out,r,ls);
    std::cout << "merge " << std::endl;
    printf_array_int<list_int>(ls);


    std::cout << "insert_sort -------------" << std::endl;
    //vector_int vc = {1,21,4,6,5,31,22};

    vector_int vc = {8193, 4099, 3073, 4110, 4113, 8195, 8213, 6166, 24, 4121, 9903, 6083, 8221, 8222, 4128, 34, 4131, 6180, 683, 2086, 2088, 4137, 4139, 2093, 4143, 6192, 4145, 4146, 4147, 8247, 4051, 6203, 6206, 8255, 9984, 6210, 6211, 8260, 70, 8266, 6219, 9618, 2127, 6224, 4177, 2130, 2132, 4183, 4185, 2138, 2142, 8289, 3430, 8296, 2154, 301, 4206, 4797, 6256, 4211, 6260, 4215, 9237, 131, 4230, 6280, 8329, 2188, 142, 365, 9923, 6292, 4247, 6296, 5256, 4255, 4256, 8354, 8355, 7916, 166, 8362, 8363, 172, 174, 6320, 6321, 5325, 6324, 8373, 5833, 2234, 187, 188, 2237, 2241, 2243, 2244, 8389, 1057, 2249, 2423, 2253, 212, 214, 377, 1060, 219, 4316, 2735, 222, 4133, 2272, 5483, 8419, 231, 232, 8426, 6382, 6383, 8433, 41, 2296, 2772, 8442, 255, 4352, 8485, 43, 4357, 2310, 8460, 2434, 8462, 6415, 273, 8921, 7556, 6191, 4381, 6432, 2337, 290, 8484, 2438, 2097, 6441, 4394, 6445, 8494, 2357, 2358, 8505, 8506, 2363, 320, 321, 4491, 7558, 4424, 2378, 5175, 6476, 3731, 338, 9273, 4441, 8538, 2395, 6490, 2397, 6494, 4447, 2413, 8559, 2416, 2417, 8254, 3817, 2452, 6526, 4479, 3136, 3153, 8580, 4486, 2441, 8586, 2443, 398, 749, 4496, 402, 2451, 404, 6549, 6551, 4504, 8602, 412, 8879, 2462, 7237, 4512, 8609, 4515, 2468, 2470, 4521, 6570, 2475, 428, 2480, 1310, 8628, 6493, 4536, 4537, 2490, 2491, 6588, 4170, 8639, 4544, 6560, 6594, 451, 6561, 2505, 458, 2513, 8608, 2519, 472, 8612, 4572, 7790, 8670, 4575, 482, 6627, 2532, 486, 5201, 8681, 8683, 8684, 495, 2544, 499, 2549, 4598, 2552, 6649, 2554, 8702, 2816, 514, 6662, 4615, 521, 1111, 526, 7597, 5268, 2577, 530, 6676, 533, 8728, 537, 4636, 541, 6687, 4641, 5894, 4649, 7996, 8748, 9650, 8750, 8751, 8754, 2611, 6708, 8678, 2615, 8760, 5556, 2618, 6715, 8765, 9701, 4674, 581, 1121, 4684, 8781, 590, 8783, 2641, 2642, 7267, 4692, 1520, 4694, 2651, 8797, 8798, 2656, 2657, 4707, 4710, 4711, 8808, 4713, 6762, 4882, 6766, 5565, 630, 4728, 4136, 8409, 4731, 2687, 4736, 641, 6251, 645, 646, 8839, 4744, 8841, 650, 6795, 4546, 2702, 8852, 8854, 4762, 9669, 9328, 4771, 7622, 2727, 3527, 6830, 6831, 432, 6836, 2742, 695, 2744, 4212, 4794, 6845, 703, 2755, 714, 4812, 2767, 9162, 8914, 724, 4822, 7289, 2777, 4826, 734, 6880, 8931, 8938, 2797, 2800, 1150, 8951, 8956, 5930, 8959, 4864, 769, 4866, 6916, 2821, 6920, 7980, 4874, 2827, 780, 6925, 6928, 2834, 6934, 8983, 4888, 2844, 8993, 4898, 8995, 8996, 3206, 6951, 809, 3573, 813, 816, 9009, 820, 821, 6893, 3209, 7256, 9019, 2878, 2880, 835, 6980, 2886, 4936, 842, 9035, 9037, 6992, 4947, 852, 9712, 9047, 7001, 7002, 2911, 4960, 4962, 827, 869, 4967, 9064, 9065, 4583, 876, 7024, 9073, 882, 9075, 4982, 2937, 6202, 2941, 7040, 2945, 4999, 904, 9097, 906, 9103, 7057, 9109, 2967, 921, 5018, 2977, 5026, 7323, 2980, 8006, 7078, 9131, 7089, 9140, 4848, 9146, 3005, 3006, 5351, 960, 3015, 3016, 5065, 970, 3019, 9164, 974, 9170, 3028, 7130, 7136, 7137, 9187, 5092, 2214, 999, 9195, 647, 3056, 3060, 3061, 7159, 3070, 3071, 1025, 5123, 5124, 3078, 7175, 5128, 1033, 5133, 5140, 3093, 1047, 7193, 1051, 7197, 1056, 9249, 7203, 3108, 3109, 7206, 2225, 7208, 3113, 9261, 3118, 5168, 1075, 1077, 3127, 9272, 1081, 3130, 7227, 1088, 7233, 7234, 4619, 9285, 8033, 7241, 9293, 7249, 9925, 7255, 5208, 5216, 9744, 9315, 9317, 3174, 7272, 3177, 871, 5228, 1134, 1979, 7282, 7699, 3188, 3189, 1142, 9335, 4628, 9338, 3198, 3201, 1154, 3203, 5252, 7302, 9313, 9352, 1266, 5261, 5262, 3218, 3244, 1172, 9366, 3227, 7326, 9377, 3236, 5285, 9382, 5287, 3240, 1196, 9391, 7344, 7345, 883, 5301, 5798, 201, 1908, 9402, 3259, 5322, 9410, 3041, 5319, 1224, 1226, 9420, 3277, 9422, 9421, 1233, 7380, 7385, 3298, 7397, 5329, 5191, 7403, 7406, 4989, 1264, 3314, 5363, 3861, 3318, 1274, 7421, 1278, 7426, 7041, 9482, 3340, 7437, 4953, 7442, 7445, 9495, 1305, 7450, 5403, 9500, 7454, 1311, 1316, 1926, 3370, 2951, 7452, 3374, 1328, 5427, 7476, 7479, 8957, 3386, 1339, 5437, 9534, 7487, 3392, 1345, 7491, 1545, 3400, 3402, 6711, 1250, 9550, 1360, 2275, 9563, 8762, 9252, 5472, 1377, 1379, 1382, 9575, 7528, 1387, 1388, 7533, 1395, 3446, 3897, 1405, 9598, 9599, 1414, 3457, 3460, 3461, 5510, 3463, 7562, 8087, 6722, 1423, 1343, 1426, 7571, 7574, 1438, 3488, 3492, 7590, 7594, 5362, 3502, 3505, 5554, 9651, 7604, 7605, 1462, 6870, 7608, 9658, 5564, 3517, 5570, 3525, 9670, 929, 1480, 8710, 3531, 3800, 1486, 5583, 7632, 3391, 9685, 1495, 9688, 7642, 3548, 5370, 3550, 2981, 9697, 9698, 5603, 3557, 1510, 7659, 9708, 1517, 5616, 1522, 3571, 9717, 7671, 7674, 7675, 9813, 5632, 9729, 5635, 3588, 1541, 7689, 5642, 9740, 9741, 9742, 7696, 3603, 5657, 5665, 3618, 3621, 7718, 9767, 8304, 3626, 1579, 5676, 1583, 5440, 3636, 6750, 9782, 1591, 9786, 7740, 9791, 7744, 7747, 3652, 9800, 7754, 7760, 7116, 3666, 2659, 9486, 3670, 5719, 7768, 7769, 3674, 5724, 9822, 7775, 1632, 1633, 2002, 5731, 5733, 1638, 1641, 9835, 9836, 5742, 3696, 1651, 7796, 9150, 7798, 617, 5753, 5055, 7805, 5056, 9858, 1667, 5764, 1669, 3139, 1672, 1674, 1676, 7825, 1682, 5779, 1646, 5648, 5784, 9881, 9883, 3740, 5789, 1648, 5794, 2331, 1702, 9897, 3754, 5063, 9654, 1710, 1711, 3358, 5815, 3769, 9917, 9919, 7872, 3778, 5827, 5750, 9926, 7881, 9930, 5751, 1747, 1657, 9944, 4047, 5852, 2562, 7902, 4389, 6779, 9961, 6060, 1772, 8146, 5870, 5651, 5875, 7926, 5881, 2346, 8149, 1792, 3843, 9990, 1802, 1803, 3714, 9998, 7951, 7952, 7955, 3860, 7957, 5910, 5904, 5082, 7970, 8838, 7978, 5931, 3884, 1838, 5935, 1841, 7986, 7988, 5942, 2699, 7993, 5946, 5948, 5949, 8003, 1860, 1861, 3910, 9185, 3914, 1868, 653, 8016, 817, 8846, 8024, 8025, 6458, 9951, 5985, 3938, 5987, 5989, 8451, 3945, 1900, 8046, 3951, 6000, 6001, 2041, 3956, 1910, 1912, 6011, 1344, 8068, 6022, 8075, 3981, 6035, 1943, 6043, 8094, 6047, 1953, 1958, 1961, 8108, 4013, 8110, 8111, 8112, 4027, 5450, 6081, 8130, 8131, 8137, 1994, 4043, 1996, 4045, 6095, 6098, 1635, 6100, 6101, 4055, 8156, 6109, 2014, 2725, 2016, 6114, 6116, 7846, 5932, 2025, 1363, 6141, 9274, 6132, 7501, 8183, 6137, 4090, 4091, 7850, 6151};
    //std::cout << "run count:" << insert_sort(vc) << std::endl; //count:218 973
    //std::cout << "run count:" << insert_sort_ex(vc,1) << std::endl; //count:218 973
    //std::cout << "run count:" << shell_sort(vc) << std::endl; //count:169 762
    //printf_array_int<vector_int>(vc);

    return 0;
}