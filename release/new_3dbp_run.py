import numpy as np
# start position
START_POSITION = [0, 0, 0]
# the posture of box
class RotationType:
    RT_WHD = 0
    RT_HWD = 1
    RT_HDW = 2
    RT_DHW = 3
    RT_DWH = 4
    RT_WDH = 5

    ALL = [RT_WHD, RT_HWD, RT_HDW, RT_DHW, RT_DWH, RT_WDH]
    # un upright or un updown
    Notupdown = [RT_WHD, RT_HWD]


# the Axis of container
class Axis:
    WIDTH = 0
    HEIGHT = 1
    DEPTH = 2

    ALL = [WIDTH, HEIGHT, DEPTH]

def rectIntersect(item1, item2, x, y):

    d1 = item1.getDimension()
    d2 = item2.getDimension()
    # 计算物体中心点
    cx1 = item1.position[x] + d1[x]/2
    cy1 = item1.position[y] + d1[y]/2
    cx2 = item2.position[x] + d2[x]/2
    cy2 = item2.position[y] + d2[y]/2

    ix = max(cx1, cx2) - min(cx1, cx2)
    iy = max(cy1, cy2) - min(cy1, cy2)
    # 判断两个物体中心距离是否小于两者拼接距离
    return ix < (d1[x]+d2[x])/2 and iy < (d1[y]+d2[y])/2


def intersect(item1, item2):
    return (
        rectIntersect(item1, item2, Axis.WIDTH, Axis.HEIGHT) and
        rectIntersect(item1, item2, Axis.HEIGHT, Axis.DEPTH) and
        rectIntersect(item1, item2, Axis.WIDTH, Axis.DEPTH)
    )



class Item:
    def __init__(self, partno, name, WHD, updown, color):
        '''

        :param partno:包装的个体序号
        :param name: 包装批次序号
        :param WHD: 宽长高
        :param updown:可否倒置
        :param color: 设置颜色
        '''
        self.partno = partno
        # The name of package
        self.name = name
        self.width = WHD[0]
        self.height = WHD[1]
        self.depth = WHD[2]
        # Upside down? True or False
        self.updown = updown
        # Draw item color
        self.color = color
        # The param of rotation
        self.rotation_type = 0
        # 放置点的起始位置
        self.position = START_POSITION


    def string(self):
        """
        :return: 数据以字符串形式显示
        """
        return "%s(%sx%sx%s) pos(%s) rt(%s) vol(%s)" % (
            self.partno, self.width, self.height, self.depth,
            self.position, self.rotation_type, self.getVolume()
        )

    def getVolume(self):
        """
        :return: 返回物体的体积
        """
        return self.width * self.height * self.depth

    def getMaxArea(self):
        """
        :return: 返回最大表面积
        """
        a = sorted([self.width, self.height, self.depth], reverse=True) if self.updown == True else [self.width,
                                                                                                     self.height,
                                                                                                     self.depth]

        return a[0] * a[1]

    def getDimension(self):
        """
        :return: 调整摆放姿态并返回
        """
        if self.rotation_type == RotationType.RT_WHD:
            dimension = [self.width, self.height, self.depth]
        elif self.rotation_type == RotationType.RT_HWD:
            dimension = [self.height, self.width, self.depth]
        elif self.rotation_type == RotationType.RT_HDW:
            dimension = [self.height, self.depth, self.width]
        elif self.rotation_type == RotationType.RT_DHW:
            dimension = [self.depth, self.height, self.width]
        elif self.rotation_type == RotationType.RT_DWH:
            dimension = [self.depth, self.width, self.height]
        elif self.rotation_type == RotationType.RT_WDH:
            dimension = [self.width, self.depth, self.height]
        else:
            dimension = []

        return dimension


class Bin:
    def __init__(self, partno, WHD, put_type=1):
        """
        :param partno: 箱体的名称
        :param WHD: 宽高长
        :param put_type: 放置姿态
        """
        self.partno = partno
        self.width = WHD[0]
        self.height = WHD[1]
        self.depth = WHD[2]

        self.items = []
        # 放置空间
        self.fit_items = np.array([[0, WHD[0], 0, WHD[1], 0, WHD[2]]])
        # 未放置包装列表
        self.unfitted_items = []
        self.fix_point = False
        self.put_type = put_type



    def string(self):
        ''' '''
        return "%s(%sx%sx%s) vol(%s)" % (
            self.partno, self.width, self.height, self.depth,
            self.getVolume()
        )

    def getVolume(self):
        """
        Get the V of the bin.
        # 获得容积集装箱
        """
        return self.width * self.height * self.depth



    def putItem(self, item, pivot, axis=None):
        """ put item in bin """
        # 设定标签fit,初始化为False
        fit = False
        # 存储item的空间初始位置
        valid_item_position = item.position
        # 更新item的空间位置属性
        item.position = pivot
        # 旋转姿态的设置
        rotate = RotationType.ALL if item.updown else RotationType.Notupdown
        # 对旋转姿态进行遍历
        for i in range(0, len(rotate)):
            # 设置当前旋转姿态
            item.rotation_type = i
            dimension = item.getDimension()

            # rotatate
            # 如果基于放置点摆放超过container尺寸，跳过当前姿态
            if (
                    self.width < pivot[0] + dimension[0] or
                    self.height < pivot[1] + dimension[1] or
                    self.depth < pivot[2] + dimension[2]
            ):
                continue
            # 如果都可以放置，则设置标签为True
            fit = True
            # 对当前存放在Bin中的item进行遍历
            for current_item_in_bin in self.items:
                # 如果返回为True，则说明无法放入（即放置点可以放置，但是无法容纳）
                if intersect(current_item_in_bin, item):
                    fit = False
                    break

            if fit:

                # 设定pivot的坐标为固定坐标时
                if self.fix_point:
                    # 当前放置姿态的尺寸
                    [w, h, d] = dimension
                    # 获得放置点坐标
                    [x, y, z] = [float(pivot[0]), float(pivot[1]), float(pivot[2])]

                    for i in range(3):
                        """
                            这里进行两次遍历的原因在于，如果每一次有一个方向的坐标参数进行的更新，
                            那么将对新的坐标参数进行另一个方向更新时，可能会导致上一次的参数失效。
                            仅进行两次遍历的原因在于，一般情况下，只会进行两次坐标调整。对于空间与时间的消耗是相对合理的。
                        """
                        # 检查左下角与右上角的坐标参数
                        # fix height
                        y = self.checkHeight([x, x + float(w), y, y + float(h), z, z + float(d)])
                        # fix width
                        x = self.checkWidth([x, x + float(w), y, y + float(h), z, z + float(d)])
                        # fix depth
                        z = self.checkDepth([x, x + float(w), y, y + float(h), z, z + float(d)])

                    self.fit_items = np.append(self.fit_items,
                                               np.array([[x, x + float(w), y, y + float(h), z, z + float(d)]]), axis=0)
                    item.position = [x, y, z]

                self.items.append(item)

            if not fit:
                item.position = valid_item_position

            return fit

        if not fit:
            # 归为原值
            item.position = valid_item_position

        return fit

    def checkDepth(self, unfix_point):
        """ fix item position z """
        z_ = [[0, 0], [float(self.depth), float(self.depth)]]
        for j in self.fit_items:
            # creat x set
            x_bottom = set([i for i in range(int(j[0]), int(j[1]))])
            x_top = set([i for i in range(int(unfix_point[0]), int(unfix_point[1]))])
            # creat y set
            y_bottom = set([i for i in range(int(j[2]), int(j[3]))])
            y_top = set([i for i in range(int(unfix_point[2]), int(unfix_point[3]))])
            # find intersection on x set and y set.
            if len(x_bottom & x_top) !=0 and len(y_bottom & y_top) !=0:
                z_.append([float(j[4]), float(j[5])])
        top_depth = unfix_point[5] - unfix_point[4]
        # find diff set on z_.
        z_ = sorted(z_, key=lambda z_: z_[1])
        for j in range(len(z_) - 1):
            if z_[j + 1][0] - z_[j][1] >= top_depth:
                return z_[j][1]
        return unfix_point[4]

    def checkWidth(self, unfix_point):
        ''' fix item position x '''
        x_ = [[0, 0], [float(self.width), float(self.width)]]
        for j in self.fit_items:
            # creat z set
            z_bottom = set([i for i in range(int(j[4]), int(j[5]))])
            z_top = set([i for i in range(int(unfix_point[4]), int(unfix_point[5]))])
            # creat y set
            y_bottom = set([i for i in range(int(j[2]), int(j[3]))])
            y_top = set([i for i in range(int(unfix_point[2]), int(unfix_point[3]))])
            # find intersection on z set and y set.
            if len(z_bottom & z_top) !=0 and len(y_bottom & y_top) !=0:
                x_.append([float(j[0]), float(j[1])])
        top_width = unfix_point[1] - unfix_point[0]
        # find diff set on x_bottom and x_top.
        x_ = sorted(x_, key=lambda x_: x_[1])
        for j in range(len(x_) - 1):
            if x_[j + 1][0] - x_[j][1] >= top_width:
                return x_[j][1]
        return unfix_point[0]

    def checkHeight(self, unfix_point):
        """
        fix item position y
        :param unfix_point: 未验证的放置item坐标点
        :return:
        """
        # 设置y尺寸的范围，包括起始位置到结束位置
        y_ = [[0, 0], [float(self.height), float(self.height)]]
        # 对当前已经放入的item进行验证
        for j in self.fit_items:
            # creat x set
            x_bottom = set([i for i in range(int(j[0]), int(j[1]))])
            x_top = set([i for i in range(int(unfix_point[0]), int(unfix_point[1]))])
            # creat z set
            z_bottom = set([i for i in range(int(j[4]), int(j[5]))])
            z_top = set([i for i in range(int(unfix_point[4]), int(unfix_point[5]))])
            # 找到交叉的坐标参数，即找到至少有同一坐标参数的坐标范围（即解决悬空问题，保证了至少是交叉）
            # find intersection on x set and z set.
            if len(x_bottom & x_top) !=0 and len(z_bottom & z_top) !=0:
                # 将当前遍历的已装入item在y方向的坐标参数添加到y_中
                y_.append([float(j[2]), float(j[3])])
        # 获得要进行放置item在y方向的坐标参数范围
        top_height = unfix_point[3] - unfix_point[2]
        # find diff set on y_bottom and y_top.
        # 对y_进行排序，从小到大排序
        y_ = sorted(y_, key=lambda y_: y_[1])
        # 对y_进行遍历，查找在y上可容纳当前item的起始y
        for j in range(len(y_) - 1):

            if y_[j + 1][0] - y_[j][1] >= top_height:
                return y_[j][1]
        # 若没找到，直接返回当前item在y方向的起始y
        return unfix_point[2]


    def clearBin(self):
        ''' clear item which in bin '''
        self.items = []
        self.fit_items = np.array([[0, self.width, 0, self.height, 0, 0]])
        return


class Packer:
    def __init__(self):
        ''' '''
        self.bins = None
        self.items = []
        self.unfit_items = []
        self.total_items = 0
        self.binding = []
        # self.apex = []

    def addBin(self, bin):
        ''' '''
        self.bins = bin
        return self.bins

    def addItem(self, item):
        ''' '''
        self.total_items = len(self.items) + 1

        return self.items.append(item)

    def pack2Bin(self, bin, item, fix_point):
        ''' pack item to bin '''
        fitted = False
        bin.fix_point = fix_point

        # bin.items为空的情况下
        if not bin.items:
            response = bin.putItem(item, item.position)

            if not response:
                # 如果未能放入container中，则将item加入unfitted_items
                bin.unfitted_items.append(item)
            return
        # 对坐标系三个方向进行遍历
        for axis in range(0, 3):
            # 获取已装箱的item的list
            items_in_bin = bin.items

            for ib in items_in_bin:
                pivot = [0, 0, 0]
                w, h, d = ib.getDimension()
                if axis == Axis.WIDTH:
                    pivot = [ib.position[0] + w, ib.position[1], ib.position[2]]
                elif axis == Axis.HEIGHT:
                    pivot = [ib.position[0], ib.position[1] + h, ib.position[2]]
                elif axis == Axis.DEPTH:
                    pivot = [ib.position[0], ib.position[1], ib.position[2] + d]
                # 在放置点进行放置，如果可行则设置fitted为True，并跳出循环
                if bin.putItem(item, pivot, axis):
                    fitted = True
                    break
            # 如果找到，则不需要继续遍历坐标系的其他方向
            if fitted:
                break
        # 如果未找到，则将当前item加入到unfitted_item中
        if not fitted:
            bin.unfitted_items.append(item)


    def putOrder(self):
        '''Arrange the order of items '''
        r = []
        # open top container
        if self.bins.put_type == 2:
            self.bins.items.sort(key=lambda item: item.position[0], reverse=False)
            self.bins.items.sort(key=lambda item: item.position[1], reverse=False)
            self.bins.items.sort(key=lambda item: item.position[2], reverse=False)
        # general container
        elif self.bins.put_type == 1:
            self.bins.items.sort(key=lambda item: item.position[1], reverse=False)
            self.bins.items.sort(key=lambda item: item.position[2], reverse=False)
            self.bins.items.sort(key=lambda item: item.position[0], reverse=False)
        else:
            pass
        return

    def pack(self, bigger_first=False, fix_point=True):
        '''pack master func '''

        self.items.sort(key=lambda item: item.getVolume(), reverse=bigger_first)
        # self.items.sort(key=lambda item: item.getMaxArea(), reverse=bigger_first)

        # pack item to bin
        for item in self.items:
            self.pack2Bin(self.bins, item, fix_point)

        for item in self.items.copy():
            if item in self.bins.unfitted_items:
                self.items.remove(item)
        # put order of items
        self.putOrder()


def get_out(box_name, wdh, num):
    lens = len(wdh)
    # init packing function
    packer = Packer()
    box = Bin(
        partno=box_name[0],
        WHD=(wdh[0][0], wdh[0][1], wdh[0][2]),
    )
    packer.addBin(box)

    for i in range(1, lens):

        for j in range(num[i]):
            packer.addItem(Item(
                partno=box_name[i]+"_D"+str(j + 1).rjust(3, '0'),
                name=box_name[i],
                WHD=(wdh[i][0], wdh[i][1], wdh[i][2]),
                updown=True,
                color="#"+str(hex(i*100000))[2:].rjust(6, '0'))
            )

    # calculate packing
    packer.pack(
        bigger_first=True,
        fix_point=True,
    )
    points = []
    b = packer.bins
    # fit rotation type
    for item in b.items:
        rt = item.rotation_type
        name = item.partno
        x, y, z = item.position
        [w, h, d] = item.getDimension()
        color = item.color
        # plot item of cube
        points.append([name, str(x), str(y), str(z), str(w), str(h), str(d), str(color)])

    return points


if __name__ == '__main__':
    box_name=["bin", "顺丰", "韵达", "百世"]
    wdh=[[600, 340, 260], [170, 82, 46], [85, 60, 60], [60, 80, 200]]
    num = [1, 15, 85, 30]
    updown=[True, True, True, True]
    points = get_out(box_name, wdh, num)
    for i in points:
        print(i)

