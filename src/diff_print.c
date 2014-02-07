	git_diff *diff;
	git_diff_format_t format;
	git_diff_line_cb print_cb;
	uint32_t flags;
	git_diff_line line;
	git_buf *out,
	git_diff *diff,
	git_diff_format_t format,
	git_diff_line_cb cb,
	void *payload)
	pi->format   = format;
	if (diff)
		pi->flags = diff->opts.flags;

	if (diff && diff->opts.id_abbrev != 0)
		pi->oid_strlen = diff->opts.id_abbrev;
	else if (!diff || !diff->repo)
	memset(&pi->line, 0, sizeof(pi->line));
	pi->line.old_lineno = -1;
	pi->line.new_lineno = -1;
	pi->line.num_lines  = 1;

static int diff_print_one_name_only(
	const git_diff_delta *delta, float progress, void *data)
	diff_print_info *pi = data;
	git_buf *out = pi->buf;

	GIT_UNUSED(progress);

	if ((pi->flags & GIT_DIFF_SHOW_UNMODIFIED) == 0 &&
		delta->status == GIT_DELTA_UNMODIFIED)
		return 0;

	git_buf_clear(out);
	git_buf_puts(out, delta->new_file.path);
	git_buf_putc(out, '\n');
	if (git_buf_oom(out))
		return -1;

	pi->line.origin      = GIT_DIFF_LINE_FILE_HDR;
	pi->line.content     = git_buf_cstr(out);
	pi->line.content_len = git_buf_len(out);

	return pi->print_cb(delta, NULL, &pi->line, pi->payload);
static int diff_print_one_name_status(
	if ((pi->flags & GIT_DIFF_SHOW_UNMODIFIED) == 0 && code == ' ')
	pi->line.origin      = GIT_DIFF_LINE_FILE_HDR;
	pi->line.content     = git_buf_cstr(out);
	pi->line.content_len = git_buf_len(out);
	return pi->print_cb(delta, NULL, &pi->line, pi->payload);
	if ((pi->flags & GIT_DIFF_SHOW_UNMODIFIED) == 0 && code == ' ')
	git_oid_tostr(start_oid, pi->oid_strlen, &delta->old_file.id);
	git_oid_tostr(end_oid, pi->oid_strlen, &delta->new_file.id);
	pi->line.origin      = GIT_DIFF_LINE_FILE_HDR;
	pi->line.content     = git_buf_cstr(out);
	pi->line.content_len = git_buf_len(out);
	return pi->print_cb(delta, NULL, &pi->line, pi->payload);
	git_oid_tostr(start_oid, oid_strlen, &delta->old_file.id);
	git_oid_tostr(end_oid, oid_strlen, &delta->new_file.id);
	return git_buf_oom(out) ? -1 : 0;
	if (git_oid_iszero(&delta->old_file.id)) {
	if (git_oid_iszero(&delta->new_file.id)) {
	GITERR_CHECK_ERROR(diff_print_oid_range(out, delta, oid_strlen));
	int error;
		 (pi->flags & GIT_DIFF_SHOW_UNTRACKED_CONTENT) == 0))
	if ((error = git_diff_delta__format_file_header(
			pi->buf, delta, oldpfx, newpfx, pi->oid_strlen)) < 0)
		return error;

	pi->line.origin      = GIT_DIFF_LINE_FILE_HDR;
	pi->line.content     = git_buf_cstr(pi->buf);
	pi->line.content_len = git_buf_len(pi->buf);
	if ((error = pi->print_cb(delta, NULL, &pi->line, pi->payload)) != 0)
		return error;
	if ((error = diff_delta_format_with_paths(
			"Binary files %s%s and %s%s differ\n")) < 0)
		return error;
	pi->line.origin      = GIT_DIFF_LINE_BINARY;
	pi->line.content     = git_buf_cstr(pi->buf);
	pi->line.content_len = git_buf_len(pi->buf);
	pi->line.num_lines   = 1;
	return pi->print_cb(delta, NULL, &pi->line, pi->payload);
	const git_diff_hunk *h,
	pi->line.origin      = GIT_DIFF_LINE_HUNK_HDR;
	pi->line.content     = h->header;
	pi->line.content_len = h->header_len;
	return pi->print_cb(d, h, &pi->line, pi->payload);
	const git_diff_hunk *hunk,
	const git_diff_line *line,
	return pi->print_cb(delta, hunk, line, pi->payload);
/* print a git_diff to an output callback */
int git_diff_print(
	git_diff *diff,
	git_diff_format_t format,
	git_diff_line_cb print_cb,
	git_diff_file_cb print_file = NULL;
	git_diff_hunk_cb print_hunk = NULL;
	git_diff_line_cb print_line = NULL;

	switch (format) {
	case GIT_DIFF_FORMAT_PATCH:
		print_file = diff_print_patch_file;
		print_hunk = diff_print_patch_hunk;
		print_line = diff_print_patch_line;
		break;
	case GIT_DIFF_FORMAT_PATCH_HEADER:
		print_file = diff_print_patch_file;
		break;
	case GIT_DIFF_FORMAT_RAW:
		print_file = diff_print_one_raw;
		break;
	case GIT_DIFF_FORMAT_NAME_ONLY:
		print_file = diff_print_one_name_only;
		break;
	case GIT_DIFF_FORMAT_NAME_STATUS:
		print_file = diff_print_one_name_status;
		break;
	default:
		giterr_set(GITERR_INVALID, "Unknown diff output format (%d)", format);
		return -1;
	}
	if (!(error = diff_print_info_init(
			&pi, &buf, diff, format, print_cb, payload)))
	{
			diff, print_file, print_hunk, print_line, &pi);

		if (error) /* make sure error message is set */
			giterr_set_after_callback_function(error, "git_diff_print");
	}
/* print a git_patch to an output callback */
int git_patch_print(
	git_patch *patch,
	git_diff_line_cb print_cb,
			&pi, &temp, git_patch__diff(patch),
			GIT_DIFF_FORMAT_PATCH, print_cb, payload)))
	{
		error = git_patch__invoke_callbacks(
		if (error) /* make sure error message is set */
			giterr_set_after_callback_function(error, "git_patch_print");
	}

	const git_diff_hunk *hunk,
	const git_diff_line *line,
	GIT_UNUSED(delta); GIT_UNUSED(hunk);
	if (line->origin == GIT_DIFF_LINE_ADDITION ||
		line->origin == GIT_DIFF_LINE_DELETION ||
		line->origin == GIT_DIFF_LINE_CONTEXT)
		git_buf_putc(output, line->origin);
	return git_buf_put(output, line->content, line->content_len);
}
/* print a git_patch to a git_buf */
int git_patch_to_buf(
	git_buf *out,
	git_patch *patch)
{
	return git_patch_print(patch, diff_print_to_buffer_cb, out);