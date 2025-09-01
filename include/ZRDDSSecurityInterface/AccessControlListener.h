#ifndef AccessControlListener_h__
#define AccessControlListener_h__

class AccessControl;
typedef void* PermissionsHandle;

class AccessControlListener
{
public:

    /**
     * @fn  bool AccessControlListener::on_revoke_permissions(const AccessControl* plugin, const PermissionsHandle* handle);
     *
     * @brief   permissionȡ����ı�ʱ���ṩһ��listener.
     *
     * @author  zch
     * @date    2018/1/31
     *
     * @param   plugin  �ͻ��˵�AccessControl.
     * @param   handle  ��Permissions����ȡ����DDS������ͨ�ŵ�Permissions��PermissionsHandle.
     *
     * @return  �ɹ�����true�����򷵻�false.
     */

   virtual bool on_revoke_permissions(
        AccessControl* plugin,
        const PermissionsHandle* handle) = 0;
};
#endif // AccessControlListener_h__
