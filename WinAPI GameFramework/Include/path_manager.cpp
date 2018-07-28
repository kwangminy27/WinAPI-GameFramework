#include "path_manager.h"

using namespace std;
using namespace filesystem;

bool PathManager::Initialize()
{
	path path_buffer = current_path();
	path_buffer.replace_filename("Bin\\");

	path_collection_.insert(make_pair("RootPath", move(path_buffer)));
	AddPath("TexturePath", "Texture\\");
	AddPath("DataPath", "Data\\");

	return true;
}

bool PathManager::AddPath(string tag, path new_path, string base_tag)
{
	if (!FindPath(tag).empty())
		return false;

	path path_buffer = FindPath(base_tag);

	if (path_buffer.empty())
		return false;

	path_buffer /= new_path;

	path_collection_.insert(make_pair(move(tag), move(path_buffer)));

	return true;
}

path const& PathManager::FindPath(string tag) const
{
	auto const iter = path_collection_.find(tag);

	if (iter == path_collection_.end())
		return path_nullptr_;

	return iter->second;
}

void PathManager::_Release()
{
}
