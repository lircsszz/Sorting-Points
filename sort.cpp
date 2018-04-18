int recognize(std::vector<cv::Point2f> &marks)

{
    if(marks.size() != 5){
        std::cout << "need 5 points" << std::endl;
        return 1;
    }

    //avg
    cv::Point2f avg(0,0);
	for(unsigned int i=0;i<marks.size();i++){
		avg += marks[i];
	}
    avg = avg / (int)marks.size();
    std::cout<<avg<<std::endl;

 
    
    cv::Mat r1,t1;

	std::cout<<marks<<std::endl;
 	for(unsigned int i=0;i<marks.size();i++)
	{
		if((marks[i].y>avg.y)) down.push_back(marks[i]);
		else other.push_back(marks[i]);
	}
	while(other.size()!=3)
	{
		down.clear();	
		other.clear();
		avg.y+=3;
		for(unsigned int i=0;i<marks.size();i++)
		{
			if(marks[i].y>avg.y) down.push_back(marks[i]);
			else other.push_back(marks[i]);
		}
	}

	sort(down.begin(),down.end(),comp);
	std::vector<float> theta_vec;
	float temp=0.0;
 	for(unsigned int i=0;i<other.size();i++)
	{
		temp=calAngles(down[0],down[1],other[i]);
		theta_vec.push_back(temp);
	}
	std::vector<ang_pts> ang_pts_vec;
	ang_pts a_p1(theta_vec[0],other[0]);
	ang_pts_vec.push_back(a_p1);
	ang_pts a_p2(theta_vec[1],other[1]);
	ang_pts_vec.push_back(a_p2);
	ang_pts a_p3(theta_vec[2],other[2]);
	ang_pts_vec.push_back(a_p3);
	sort(ang_pts_vec.begin(),ang_pts_vec.end(),comp2);

	std::vector<cv::Point2f> other_sorted;
 	for(unsigned int i=0;i<other.size();i++)
	{
		other_sorted.push_back(ang_pts_vec[i].pts);
	}	
	std::vector<cv::Point2f> other_sorted_copy(other_sorted);
	int min_L_id=findMinL(other_sorted);
	other_sorted.erase(other_sorted.begin()+min_L_id);
	temp1.push_back(other_sorted[1]);
	temp1.push_back(other_sorted[0]);
	temp1.push_back(down[1]);
	temp1.push_back(down[0]);
	temp1.push_back(other_sorted_copy[min_L_id]); 
	
    if(temp1.size()!=5) {
		return 1;
	}
	Debug("temp1");
	Debug(temp1);
	
    float err = calError(temp1,r1,t1);//PnP
    //R = r1;
    //T = t1;
	Debug("err");//use debugview to show the result
	Debug(err);
    return 2;
}
